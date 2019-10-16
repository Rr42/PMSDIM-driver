/*
* File name: PMSDInterfacer.h
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: PMSD Interface Module driver
* Description: 
* 	This code provides declarations for the Interfacer structure for the virtual device instance.
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

#ifndef __PMSD_INTERFACER__
#define __PMSD_INTERFACER__

/* Allows access to semaphores for sychronization, helps privent corruption due to multiple threads accessing the same data */
#include <linux/semaphore.h>

/* Data structure for virtual device */
struct PMSDInterfacer
{
    char command[2];
    char result[5];

    /* Privent data corruption */
    struct semaphore sem;
};

#endif
