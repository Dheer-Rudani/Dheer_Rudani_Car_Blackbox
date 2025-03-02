/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */

#ifndef CARBLACKBOX_H
#define	CARBLACKBOX_H

//KEYS
#define SW1 1
#define SW2 2
#define SW3 3
#define SW4 4
#define SW5 5
#define SW6 6
#define SW7 7
#define SW8 8
#define SW9 9
#define SW10 10
#define SW11 11
#define SW12 12


//Initialization
//CLCD
#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7


#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0
#define _XTAL_FREQ                                   20000000
#define LINE1(x)									(0x80 + (x))
#define LINE2(x)                                    (0xC0 + (x))

#define TWO_LINE_5x8_MATRIX_8_BIT					clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN				            clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME                                 clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF						clcd_write(0x0C, INSTRUCTION_COMMAND)
#define EIGHT_BIT_MODE                                  0x33
void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);


//Matrix keypad
void init_kpad();
unsigned char read_kpad();
unsigned char scan_key();

//ADC
void init_adc();
unsigned short read_adc();

//enum
typedef enum 
{
    DASH_BOARD,
    MAIN_MENU,
    VIEW_LOG,
    CLEAR_LOG,
    DOWNLOAD_LOG,
    SET_TIME
}type;

//Other declarations
void dash_board();
void main_menu();
unsigned char gears[8][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "GR", " C"};
unsigned char time[] = "00:00:00", speed[] = "00"; 
unsigned char key, count = 0, adc = 0, i = 0, j = 0, f1 = 0, view_size = 0, read_add = 0, f4 = 1, reset_count = 0, rcount = 0;
unsigned char clock_reg[3], view[10][17];
void view_log();
void clear_log();

//EEPROM internal
unsigned char read_value(unsigned char);
void write_value(unsigned char, unsigned char);
unsigned char address = 0x00;

//RTC 
#define SLAVE_READ		0xD1
#define SLAVE_WRITE		0xD0

//EEPROM
#define READ_EEPROM     0xA1
#define WRITE_EEPROM    0xA0

#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07

void init_ds1307(void);
void write_ds1307(unsigned char address1,  unsigned char data);
unsigned char read_ds1307(unsigned char address1);
void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);
void get_time(void);
void set_time(void);
void read_eeprom();
void write_eeprom(unsigned char address, unsigned char data);
unsigned char read_ext_eeprom(unsigned char address);

//UART
#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void putch(unsigned char byte);
int puts(const char *s);
unsigned char getch(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);
void init_uart(void);
void download_log();

#endif	/* CARBLACKBOX_H */

