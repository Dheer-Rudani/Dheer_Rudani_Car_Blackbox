/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */


#include <xc.h>
#include "carblackbox.h"

extern unsigned char once,x,state;//Accessing the declared global variables

unsigned char flag = 0,f3 = 1;//Control flags
//int temp = 0;//Checking variable

void store()
{
//    temp = address; //To display the value (checking)
    
    //Storing the values in internal EEPROM
    write_eeprom(address++, time[0]);
    write_eeprom(address++, time[1]);
    write_eeprom(address++, time[3]);
    write_eeprom(address++, time[4]);
    write_eeprom(address++, time[6]);
    write_eeprom(address++, time[7]);
    write_eeprom(address++, gears[count][0]);
    write_eeprom(address++, gears[count][1]);
    write_eeprom(address++, speed[0]);
    write_eeprom(address++, speed[1]);
    if(address == 0x64)
        address = 0x00;
    
    //Size count for accessing the stored values from the EEPROM
    if(view_size < 10)
        view_size++;
    
    //Monitoring variable to reset the read_add
    reset_count++;
    
    //Resetting the read_address to display the new readings at the end.
    if(reset_count > 10 && reset_count < 249)
    {
         read_add = 10 * (reset_count % 10);
    }
    else if(reset_count == 250)
    {
        read_add = 0;
        reset_count = 0;
    }
    else
        read_add = 0;
    
    //Resetting the read flag to read the new values stored
    once = 1;
    x = 0;
    
//    //To display value stored (checking)
//    char str[11];
//    int j = 0;
//    for ( int i = temp; i < temp+10; i++)
//    {
//        str[j++] = read_ext_eeprom(i);
//    }
//    str[10] = '\0';
//    clcd_print(str,LINE1(0));
//    for ( unsigned long int wait=300000;wait--;);
//    CLEAR_DISP_SCREEN;
}

void dash_board()
{   
    //Read keypad
    if(flag == 0)
    {
        //Gear Control (Inc)
        if (key == SW2) {
            if (count < 6) {
                count++;
                store();
            } else
                count = 6;

        }            
        //Gear Control (Dec)
        else if (key == SW3) {
            if (count > 1) {
                count--;
                store();
            } else
                count = 1;
        }            
        //Gear Control (C)
        else if (key == SW1) {
            flag = 1;
            count = 7;
            store();
        }

        //Speed Control
        adc = read_adc()/10.32; //Scaling it to 0-99;
        speed[0] = adc/10 + '0';
        speed[1] = adc%10 + '0';
    }
    
    //Crash Condition
    if(flag == 1)
    {   
        //Gear Control (GN)
        if(key == SW2 || key == SW3)
        {
            count = 1;
            store();
            flag = 0;
        }
    }
    
    //Display values
    clcd_print(time, LINE2(0));
    clcd_print(gears[count], LINE2(10));
    clcd_print(speed, LINE2(14)); 
    
    //Condition to enter main-menu 
    if(key == SW11)
    {
        state = MAIN_MENU;
        f4 = 1;//Resetting the read time flag
        CLEAR_DISP_SCREEN;
    }
}

