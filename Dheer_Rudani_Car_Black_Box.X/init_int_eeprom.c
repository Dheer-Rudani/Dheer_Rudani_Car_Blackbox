/*
 * File:   init_int_eeprom.c
 * Author: dheer
 *
 * Created on 2 January, 2025, 2:13 PM
 */


#include <xc.h>
#include "carblackbox.h"

unsigned char read_value(unsigned char address)
{
    //Storing the address
    EEADR = address;
    
    //Disabling the write enable register
    EECON1bits.WREN = 0;
    
    //Setting the memory to EEPROM
    EECON1bits.EEPGD = 0;
    
    //Setting the access to data
    EECON1bits.CFGS = 0;
    
    //Initiating the read only mode
    EECON1bits.RD = 1;
    
    //Returning the data stored
    return EEDATA;
}

void write_value(unsigned char address, unsigned char data)
{
    //Storing the address
    EEADR = address;
    
    //Storing the data
    EEDATA = data;
    
    //Setting the memory to EEPROM
    EECON1bits.EEPGD = 0;
    
    //Setting the access to data
    EECON1bits.CFGS = 0;
    
    //Enabling the write enable register
    EECON1bits.WREN = 1;
    
    //Disabling the interrupts
    GIE = 0;
    
    //Configuring the protection sequence
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    //Initiating the write mode
    EECON1bits.WR = 1;
     
    //Enabling the interrupts
    GIE = 1;
     
    //Waiting till writing is complete
    while(!PIR2bits.EEIF);
        PIR2bits.EEIF = 0; //Resetting the flag for next iteration
}