/*
 * File:   init_adc.c
 * Author: dheer
 *
 * Created on 31 December, 2024, 2:06 PM
 */


#include <xc.h>

void init_adc()
{
    //ADCON0
    //Channel select
    CHS3 = 0;
    CHS2 = 1;
    CHS1 = 0;
    CHS0 = 0;
    
    //NO conversion
    GO = 0;
    
    //Enabling the ADC
    ADON = 1;
    
    //ADCON1
    //No Reference Voltage
    VCFG1 = 0;
    VCFG0 = 0;
    
    //Make AN4 as Analog
    PCFG3 = 1;
    PCFG2 = 0;
    PCFG1 = 0;
    PCFG0 = 0;
    
    //To clear the garbage value
    ADRESH = ADRESL = 0x00;
    
    //ADCON2
    //Selecting the clock-speed
    ADCS2 = 0;
    ADCS2 = 1;
    ADCS2 = 0;
    
    //Selecting the acquisition time
    ACQT2 = 1;
    ACQT1 = 0;
    ACQT0 = 0;
    
    //Right justified
    ADFM = 1;
}

unsigned short read_adc()
{
    GO = 1;
    while(GO);
    return (ADRESL | (ADRESH << 8));
}

