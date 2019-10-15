/*
* File name: UappPMSDIM.c
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: PMSD Interface Module driver sample user application
* Description: 
*   This is a sample code to demonstrate the use of PMAD interface module driver on the Raspberry Pi 3B.
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

#include "UappPMSDIM.h"

int main(void)
{
    // int i;
    char ch, io_buf[20];

    int fp = open(DEVICE, O_RDWR);

    if(fp == -1)
    {
        printf("file %s either does not exist or has been locked by another user\n", DEVICE);
        exit(-1);
    }

    printf("1. \'r\' for reading data from device\n2. \'w\' for writing data to device\nEnter option: ");
    scanf("%c", &ch);

    switch (ch)
    {
    case 'r':
        read(fp, io_buf, sizeof(io_buf));
        printf("Data: %s\n", io_buf);
        break;
    case 'w':
        printf("Enter data: ");
        scanf(" %[^\n]", io_buf);
        printf("io_buf: %s\nio_buf_len: %d\n", io_buf, strlen(io_buf));
        write(fp, io_buf, strlen(io_buf));
        break;
    default:
        printf("Invalid input\n");
        break;
    }

    close(fp);
    return 0;
}
