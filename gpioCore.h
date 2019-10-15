/*
* File name: gpioCore.h
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: PMSD Interface Module driver
* Description: 
* 	This code provides declarations for the core GPIO functionality required by the PMSD Interface Module driver.
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
#include <linux/gpio.h>
// #include "/usr/include/wiringPi.h"

/* GPIO number for indicator LED */
#define INDICATOR_LED 5

/* Possible GPIO pin states */
#define LOW 0
#define HIGH 1

/* Functions */
int gpioInit(void);
int gpioSetSignalL(void);
int gpioSetSignalH(void);
int gpioExit(void);
