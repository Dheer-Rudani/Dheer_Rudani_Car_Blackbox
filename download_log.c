/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */


#include <xc.h>
#include "carblackbox.h"

extern unsigned char state, once;

void download_log()
{
    //Printing the logs through UART if they are present
    if (view_size != 0) {
        //reading the values if not read
        if(once == 1){
            read_eeprom();
            once = 0;
        }
        puts("----------------------\n\r");
        puts("Printing the logs.....\n\r");
        puts("----------------------\n\r");
        puts("# TIME     EV SP\n\r");
        puts("----------------------\n\r");
        clcd_print("DOWNLOADING....", LINE1(0));
        clcd_print("THROUGH UART....", LINE2(0));
        for (unsigned char uart = 0; uart < view_size; uart++) {
            puts(view[uart]);
            puts("\n\r");
        }
        puts("----------------------\n\r");
        puts("\n\r");
    } else {
        puts("----------------------\n\r");
        puts("No logs available...\n\r");
        puts("----------------------\n\n\r");
        clcd_print("NO LOGS TO", LINE1(0));
        clcd_print("DOWNLOAD :(", LINE2(5));
    }
    for(unsigned long int wait = 800000; wait--;);//Delay
    CLEAR_DISP_SCREEN;
    state = MAIN_MENU;
    //Resetting the control variables
    i = 0;
    j = 0;
}