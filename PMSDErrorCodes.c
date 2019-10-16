/*
* File name: PMSDErrorCodes.c
* Code author: Ramana R (github@Rr42)
* Code version: v1.0.1
* Application: PMSD Interface Module driver
* Description: 
* 	This code provides definitions for error codes used in the PMSD IM application.
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

#include "PMSDErrorCodes.h"

const char ECODE_OK[2] = "0\0";
const char ECODE_FAIL[3] = "-1\0";

int DUMMY_FUNCTION(char var)
{
    return RT_OK;
}
