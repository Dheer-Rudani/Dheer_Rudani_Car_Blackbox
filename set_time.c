/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */


#include <xc.h>
#include "carblackbox.h"

unsigned char hour = 0, min = 0, sec = 0, count1 = 0, time_set[9] = "00:00:00" ,k = 0, hour_bcd, min_bcd, sec_bcd;
extern unsigned char state;

void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
}

void store_time()
{
    hour_bcd = ((hour / 10) << 4) | (hour % 10);
    min_bcd = ((min / 10) << 4) | (min % 10);
    sec_bcd = ((sec / 10) << 4) | (sec % 10);
    
    write_ds1307(HOUR_ADDR, hour_bcd);
    write_ds1307(MIN_ADDR, min_bcd);
    write_ds1307(SEC_ADDR, sec_bcd);
}

void set_time(void)
{  
    //Control
    if(key == SW1)
    {
        if(count1 == 2)
        {
            if(sec < 59)
                sec++;
            else
                sec = 0;
        }
        else if(count1 == 1)
        {
            if(min < 59)
                min++;
            else
                min = 0;
        }
        else if(count1 == 0)
        {
            if(hour < 23)
                hour++;
            else
                hour = 0;
        }
    }
    else if(key == SW2)
    {
        if(count1 < 2)
            count1++;
        else
            count1 = 0;
        time_set[0] = hour/10 + '0';
        time_set[1] = hour%10 + '0';
        time_set[3] = min/10 + '0';
        time_set[4] = min%10 + '0';
        time_set[6] = sec/10 + '0';
        time_set[7] = sec%10 + '0'; 
    }
    else if(key == SW11)
    {
        store_time();
        i = 0;
        j = 0;
        state = DASH_BOARD;
    }
    
    //Reading the data only for once when we enter this function
    if(f4 == 1)
    {
        hour = ((time[0] - 48) * 10) + (time[1] - 48);
        min = ((time[3] - 48) * 10) + (time[4] - 48);
        sec = ((time[6] - 48) * 10) + (time[7] - 48);
        f4 = 0;
    }
    
    //Display
    if(++k == 100)
    {
        time_set[0] = hour/10 + '0';
        time_set[1] = hour%10 + '0';
        time_set[3] = min/10 + '0';
        time_set[4] = min%10 + '0';
        time_set[6] = sec/10 + '0';
        time_set[7] = sec%10 + '0';
        
    }
    else if(k == 200)
    {
        if(count1 == 0){
            time_set[0] = ' ';
            time_set[1] = ' ';}
        else if(count1 == 1){
            time_set[3] = ' ';
            time_set[4] = ' ';}
        else if(count1 == 2){
            time_set[6] = ' ';
            time_set[7] = ' ';}
        k = 0;
    }
    
    clcd_print(time_set, LINE2(0));
}