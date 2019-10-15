/*
* File name: UappPMSDIM.h
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: PMSD Interface Module driver sample user application
* Description: 
*   This is a sample code that provides definitions for the demonstration of 
*   the PMAD interface module driver on the Raspberry Pi 3B.
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define DEVICE "/dev/PMSDIMDriver"

int main(void);
