/*
 * Name: DHEER RUDANI
 * Description: Car_Black_Box
 * Date: 15 January, 2025
 */

#include <xc.h>
#include "carblackbox.h"

/* 
 * DS1307 Slave address
 * A0  -  Write Mode
 * A1  -  Read Mode
 */

void write_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(WRITE_EEPROM);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(unsigned int wait = 3000; wait--;);
}

unsigned char read_ext_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(WRITE_EEPROM);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(READ_EEPROM);
	data = i2c_read();
	i2c_stop();

	return data;
}
