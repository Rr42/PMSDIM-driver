/*
* File name: PMSDErrorCodes.h
* Code author: Ramana R (github@Rr42)
* Code version: v1.0.1
* Application: PMSD Interface Module driver
* Description: 
* 	This code provides declarations for error codes used in the PMSD IM application.
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

#ifndef __PMSD_ERROR_CODES__
#define __PMSD_ERROR_CODES__

/* PMSD internal return codes */
#define RT_OK 0
#define RT_FAIL -1
#define RT_WARNING -2
#define RT_FATAL -3
#define RT_UNMET_CONDITION -4
#define RT_UNKNOWN_ERROR -100

/* System return codes */
#define SYRT_OK 0;
#define SYRT_FATAL -1

/* Device error codes */
extern const char ECODE_OK[2];// = "0\0";
extern const char ECODE_FAIL[3];// = "-1\0";

/* Dummy function to be used as placeholder for future functionality */
int DUMMY_FUNCTION(char var);

#endif
