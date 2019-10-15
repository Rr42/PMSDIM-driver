/* 
* File name: PMSDIMDriver.c
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: PMSD Interface Module driver
* Description:
*   This is a Linux driver module built to work with the PMSD interface module and allow
*   communication between higher level user applications and the interface module.
* License:
*   Copyright (C) 2019  Ramana R (github@Rr42)
*   
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*   
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*   
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* Includes */
#include <linux/module.h>
#include <linux/kernel.h>
/* File operations structure, allows to open/close, read/write to the device */
#include <linux/fs.h> 
/* Char driver for character device drivers */
#include <linux/cdev.h>
/* Allows access to semaphores for sychronization, helps privent corruption due to multiple threads accessing the same data */
#include <linux/semaphore.h>
/* Access and map data from user space to kernel space; copy_to_user,copy_from_user */
#include <linux/uaccess.h>
/* Include GPIO functionality */
#include "gpioCore.h"
/* Include for handling character data */
#include <linux/string.h>

/* Data structure for virtual device */
struct fake_device 
{
    char command[2];
    char result[5];

    /* Privent data corruption */
    struct semaphore sem;
} virtual_device;

/* myCDEV */
struct cdev *mcdev;
/* holes major number */
int major_number;
/* holds return value */
int ret;
/* holds major number that kernel gives as a structure*/
dev_t dev_num;

/* Max minor number */
#define MX_MINOR 1

/* define the device name */
#define DEVICE_NAME "PMSDIMD"

/* Error codes */
const char ECODE_OK[2] = "0\0";
const char ECODE_FAIL[3] = "-1\0";

/* Device open function */
int PMSDIMdriver_open(struct inode *inode, struct file *filp)
{
    /* Lock the device using semiphore to privent other modules from using the device at the same time */
    if(down_interruptible(&virtual_device.sem) != 0)
    {
        printk(KERN_ALERT "PMSDIMD: could not lock device\n");
        return -1;
    }

    printk(KERN_INFO "PMSDIMD: Device opened\n");
    return 0;
}

/* Device read function */
ssize_t PMSDIMdriver_read(struct file *filp, char *bufStoreData, size_t bufCount, loff_t *curoffset)
{
    char data[20];
    /* Take data from kernel space (device) to user space (process) */
    printk(KERN_INFO "PMSDIMD: Reading from device\n");

    sprintf(data, "{ C:%s, R:%s }", virtual_device.command, virtual_device.result);

    /* (<destination>, <source>, <sizeToTransfer>) */
    ret = copy_to_user(bufStoreData, data, bufCount);
    return ret;
}

/* Device write function */
ssize_t PMSDIMdriver_write(struct file *filp, const char *bufStoreData, size_t bufCount, loff_t *curoffset)
{
    /* Take data from user space (process) to kernel space (device)*/
    printk(KERN_INFO "PMSDIMD: Writing to device\n");

    /* (<destination>, <source>, <sizeToTransfer>) */
    ret = copy_from_user(virtual_device.command, bufStoreData, bufCount);

    switch(virtual_device.command[0])
    {
        case '0':
            strcpy(virtual_device.result, ( (gpioSetSignalL() >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ) );
        break;
        case '1':
            strcpy(virtual_device.result, ( (gpioSetSignalH() >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ));
        break;
        default:
            strcpy(virtual_device.result, (const char*)&ECODE_FAIL);
        break;
    }

    return ret;
}

/* Device close function */
int PMSDIMdriver_close(struct inode *inode, struct file *filp)
{
    /* remove lock on device */
    up(&virtual_device.sem);
    printk(KERN_INFO "PMSDIMD: Device closed\n");
    return 0;
}

/* File opperations structure */
struct file_operations fops = {
    /* Privents unloading of module when operations are running */
    .owner = THIS_MODULE,
    .open = PMSDIMdriver_open,
    .release = PMSDIMdriver_close,
    .write = PMSDIMdriver_write,
    .read = PMSDIMdriver_read
};


/* Init function */
static int PMSDIMdriver_init(void)
{
    /* Registering device */
    /* Step 1 */
    /* Get major number and allocate char device region */
    ret = alloc_chrdev_region(&dev_num, 0, MX_MINOR, DEVICE_NAME);
    /* alloc_cdev_region(<device structure>, <startime major number>, <maximum minor number>, <device name>)*/

    if(ret < 0)
    {
        /* exit on error */
        printk(KERN_ALERT "PMSDIMD: failed to allocate major number\n");
        return ret;
    }

    /* Extract the major number */
    major_number = MAJOR(dev_num);
    printk(KERN_INFO "PMSDIMD: major number is %d\n", major_number);
    printk(KERN_INFO "PMSDIMD: use \"mknod /dev/%s c %d 0\" for device file\n", DEVICE_NAME, major_number);

    /* Step 2 */
    /* Allocate char device structure */
    mcdev = cdev_alloc();
    /* Structure for file opperations */
    mcdev->ops = &fops;
    mcdev->owner = THIS_MODULE;
    /* Add cdev to kernel */
    ret = cdev_add(mcdev, dev_num, MX_MINOR);
    if(ret < 0)
    {
        printk(KERN_ALERT "PMSDIMD: Failed to add cdev to kernel\n");
    }

    /* Init the semaphore with initial value of 1 */
    sema_init(&virtual_device.sem, 1);

    ret = gpioInit();
    if (ret < 0)
    {
        printk(KERN_ALERT "PMSDIMD: failed to allocate IO pin\n");
        return ret;
    }

    printk(KERN_INFO "PMSDIMD: Module loaded\n");
    return 0;
}

/* Exit function */
static void PMSDIMdriver_exit(void)
{
    gpioExit();
    
    /* unregister everything in reverse order */
    cdev_del(mcdev);

    unregister_chrdev_region(dev_num, MX_MINOR);
    printk(KERN_ALERT "PMSDIMD: unloaded module\n");
}

module_init(PMSDIMdriver_init);
module_exit(PMSDIMdriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rr42");
MODULE_DESCRIPTION("PMSD interface module driver");
MODULE_VERSION("1.0");
