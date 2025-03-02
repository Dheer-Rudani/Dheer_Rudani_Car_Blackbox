/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */

/*
 * Directions to use
 * -> In DASH_BOARD
 *    SW1 -> Crash (C)
 *    SW2 -> GEAR_UP
 *    SW3 -> GEAR_DOWN
 *    SW11 -> MAIN_MENU
 * 
 * -> In MAIN_MENU
 *    SW1 -> Scroll UP
 *    SW2 -> Scroll DOWN
 *    SW11 -> Enter Selection
 *    SW12 -> BACK
 * 
 * -> In VIEW_LOG
 *    SW1 -> Next Reading
 *    SW2 -> Previous Reading
 *    SW12 -> BACK
 * 
 * -> In SET_TIME
 *    SW1 -> Increment Value
 *    SW2 -> Change Field
 *    SW11 -> Save the time and goto DASH_BOARD
 *    SW12 -> Don't save and goto MAIN_MENU
 */

#include <xc.h>
#include "carblackbox.h"

unsigned char state = DASH_BOARD; //Initial state condition

//Initializations
void init_config()
{
    //LCD,ADC,MKPAD
    init_clcd();
    init_adc();
    init_kpad();
    
    //UART
    init_uart();
    
    clcd_print(gears[0], LINE2(10));
    
    speed[0] = adc/10 + '0';
    speed[1] = adc%10 + '0';
    clcd_print(speed, LINE2(14));  
    
    //I2C
    init_clcd();
	init_i2c();
	init_ds1307();
	clcd_print(time, LINE2(0));
    
}

//The main function
void main(void) {
    init_config();//Initialization function call
    while(1)
    {
        get_time();//Getting the RTC readings
        key = read_kpad();//Getting the switch pressed status
        
        //Condition to go BACK
        if(key == SW12){
            if(state != DASH_BOARD){
                if(state != MAIN_MENU)
                    state = MAIN_MENU;
                else
                    state = DASH_BOARD;
                f4 = 1;
            }
            
            //Resetting the selections and the flag variable
            i = 0;
            j = 0;
            f1 = 0;
            CLEAR_DISP_SCREEN;
        }
        
        //Control Switch
        switch(state)
        {
            case DASH_BOARD: 
                clcd_print("TIME      EV  SP", LINE1(0));
                dash_board();
                break; 
            case MAIN_MENU:
                main_menu();
                break;
            case VIEW_LOG:
                clcd_print("# VIEW LOG :", LINE1(0));
                view_log();
                break;
            case CLEAR_LOG:
                clear_log();
                break;
            case DOWNLOAD_LOG:                  
                download_log();               
                break;
            case SET_TIME:
                clcd_print("SET TIME", LINE1(0));
                set_time();
                break;
        }
    }
    return;
}
