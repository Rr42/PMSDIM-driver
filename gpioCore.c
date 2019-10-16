/*
* File name: gpioCore.c
* Code author: Ramana R (github@Rr42)
* Code version: v1.0.1
* Application: PMSD Interface Module driver
* Description: 
*   This code provides definitions for the core GPIO functionality required by the PMSD Interface Module driver.
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

#include "gpioCore.h"

int gpioInit(void)
{
    int ret = gpio_request(INDICATOR_LED, "sysfs");
    
    if (ret != 0)
        return ret;
    
    ret = gpio_direction_output(INDICATOR_LED, LOW);
    ret -= gpio_export(INDICATOR_LED, false);

    return ret;
}

int gpioSetSignalL(void)
{
    gpio_set_value(INDICATOR_LED, LOW);
    return RT_OK;
}

int gpioSetSignalH(void)
{
    gpio_set_value(INDICATOR_LED, HIGH);
    return RT_OK;
}

int gpioExit(void)
{
    gpio_unexport(INDICATOR_LED);
    gpio_free(INDICATOR_LED);

    return RT_OK;
}

/* Interfacer commands
* Test commands (GPIO):
*   'T0'  : SET TEST_LED LOW
*   'T1'  : SET TEST_LED HIGH
* Read commands (ADC):
*   'R1'  : READ ADC 1_SAMPLE 
*   'RNn' : READ ADC N_SAMPLE n
* Write commands (DMUX):
*   'W1'  : WRITE DMUX 1_SAMPLE
*   'WNn' : WRITE DMUX N_SAMPLE n
 */
int interfacerExecute(struct PMSDInterfacer *interfacer)
{
    switch( (*interfacer).command[0] )
    {
        case 'T':
            switch( (*interfacer).command[1] )
            {
                case '0':
                    strcpy((*interfacer).result, ( (gpioSetSignalL() >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ) );
                    break;

                case '1':
                    strcpy((*interfacer).result, ( (gpioSetSignalH() >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ));
                    break;

                default:
                    strcpy((*interfacer).result, (const char*)&ECODE_FAIL);
                    return RT_UNMET_CONDITION;
            }
        break;

        case 'R':
            switch( (*interfacer).command[1] )
            {
                case '1':
                    strcpy((*interfacer).result, ( (DUMMY_FUNCTION('0') >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ) );
                break;

                case 'N':
                    strcpy((*interfacer).result, ( (DUMMY_FUNCTION( (*interfacer).command[2] ) >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ) );
                    break;

                default:
                    strcpy((*interfacer).result, (const char*)&ECODE_FAIL);
                    return RT_UNMET_CONDITION;
            }
            break;
        
        case 'W':
            switch( (*interfacer).command[1] )
            {
                case '1':
                    strcpy((*interfacer).result, ( (DUMMY_FUNCTION('0') >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ) );
                break;

                case 'N':
                    strcpy((*interfacer).result, ( (DUMMY_FUNCTION( (*interfacer).command[2] ) >= 0)?(const char*)&ECODE_OK:(const char*)&ECODE_FAIL ) );
                    break;

                default:
                    strcpy((*interfacer).result, (const char*)&ECODE_FAIL);
                    return RT_UNMET_CONDITION;
            }
            break;

        default:
            strcpy((*interfacer).result, (const char*)&ECODE_FAIL);
            return RT_UNMET_CONDITION;
    }

    return RT_OK;
}
