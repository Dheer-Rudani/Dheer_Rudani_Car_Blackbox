/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */


#include <xc.h>
#include "carblackbox.h"

extern unsigned char state;
unsigned char x = 0, once = 1; //Display Control variables

//Function to read from external EEPROM
void read_eeprom()
{
    for(unsigned char i = 0; i < view_size; i++)
    {
        for(unsigned char j = 0; j < 16; j++)
        {
            if(j == 0)
                view[i][j] = i + '0';
            else if(j == 4 || j == 7)
                view[i][j] = ':';
            else if(j == 1 || j == 10 || j == 13)
                view[i][j] = ' ';
            else
                view[i][j] = read_ext_eeprom(read_add++);
        }
        view[i][16] = '\0';
        if(read_add == 0x64)
            read_add = 0x00;
    }
}

//Function to display the events
void view_log()
{
    //Displaying based upon whether the logs are present or not
    if(view_size == 0)
    {
        CLEAR_DISP_SCREEN;
        clcd_print("NO LOGS TO", LINE1(0));
        clcd_print("DISPLAY :(...", LINE2(3));
        for(unsigned long wait = 800000;wait--;);
        state = 1;
        CLEAR_DISP_SCREEN;
    }
    else if(view_size != 0)
    {
        
        if(key == SW1)
        {
            if(x < (view_size - 1))
                x++;
        }
        else if(key == SW2)
        {
            if(x > 0)
                x--;    
        }
        
        //Initially Storing the values for printing
        if(once == 1)
        {
            read_eeprom();
            once = 0;
        }

        clcd_print(view[x], LINE2(0));       
    }
}

//Function to clear log
void clear_log()
{
    clcd_print("CLEARING THE",LINE1(0));
    clcd_print("LOGS.....",LINE2(7));
    view_size = 0;
    address = 0x00;
    reset_count = 0;
    for(unsigned long int wait = 800000; wait--;);
    CLEAR_DISP_SCREEN;
    state = MAIN_MENU;
    //Resetting the control variables
    i = 0;
    j = 0;
}