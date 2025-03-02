/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */


#include <xc.h>
#include "carblackbox.h"

char disp[4][13] = { "VIEW LOG", "CLEAR LOG", "DOWNLOAD LOG" , "SET TIME" };//2D array to display the following strings on LCD
extern unsigned char state;//Accessing the global variable

void main_menu()
{
    //Displaying the values on LCD
    //Pointer display control
    if(i == 0)
        clcd_putch('*', LINE1(0));
    else if(i == 1)
        clcd_putch('*', LINE2(0));
    
    clcd_print(disp[j],LINE1(1));
    clcd_print(disp[j+1], LINE2(1));
    
    if(key == SW2)
    {
        //Pointer and 2D array movement(Inc) control
        if(i < 1)
            i++;
        else if(i == 1 && j < 2)
            j++;
        CLEAR_DISP_SCREEN;
    }
    else if(key == SW1)
    {
        //Pointer and 2D array movement(Dec) control
        if(i > 0)
            i--;
        else if(i == 0 && j > 0)
            j--;
        CLEAR_DISP_SCREEN;
    }
    else if(key == SW11 && f1 == 1)
    {
        //State control based upon pointing of pointer
        CLEAR_DISP_SCREEN;
        if (i == 0 && j == 0)
            state = VIEW_LOG;
        else if ((i == 0 && j == 1) || (i == 1 && j == 0))
            state = CLEAR_LOG;
        else if ((i == 1 && j == 1) || (i == 0 && j == 2))
            state = DOWNLOAD_LOG;
        else if (i == 1 && j == 2)
            state = SET_TIME;
    }
    
    //Setting the flag for selection
    f1 = 1;
}

