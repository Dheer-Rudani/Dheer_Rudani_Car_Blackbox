/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */


#include <xc.h>

void init_kpad()
{
    TRISB = 0x1E;
    RBPU = 0;
    RB5 = RB6 = RB7 = 1;
}

unsigned char scan_key()
{
    RB5 = 0;
    RB6 = RB7 = 1;
    if(RB1 == 0)
        return 1;
    else if(RB2 == 0)
        return 4;
    else if(RB3 == 0)
        return 7;
    else if(RB4 == 0)
        return 10;
    
    RB6 = 0;
    RB5 = RB7 = 1;
    if(RB1 == 0)
        return 2;
    else if(RB2 == 0)
        return 5;
    else if(RB3 == 0)
        return 8;
    else if(RB4 == 0)
        return 11;
    
    RB7 = 0;
    RB5 = RB6 = 1;
    if(RB1 == 0)
        return 3;
    else if(RB2 == 0)
        return 6;
    else if(RB3 == 0)
        return 9;
    else if(RB4 == 0)
        return 12;
    
    return 0xFF;
}

//Setting the matrix keypad to edge triggering
unsigned char read_kpad()
{
    static unsigned char ch = 1;
    unsigned char key = scan_key();
    if((key != 0xFF) && ch)
    {
        ch = 0;
        return key;
    }
    else if(key == 0xFF)
        ch = 1;
    return 0xFF;
}
