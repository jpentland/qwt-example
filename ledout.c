/* This file contains implementations of functions
 * for interacting with the LED output device
 * as part of the volume meter application
 *
 * For more information, see ledout.h
 *
 * Author: Joseph Pentland <0804325p@student.gla.ac.uk>
 * Created: 7 March 2013
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define I2CADDR 0x20
#define PORTA_REG_ADDR 0x14
#define PORTA_DD_REG_ADDR 0x00

static int file;
static int dmin;
static int dmax;

int writeReg(unsigned char reg_addr, unsigned char data) {
	 
	unsigned char buff[2];
	int retVal = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[1];
									 
	buff[0] = reg_addr;
	buff[1] = data;
													 
	messages[0].addr = I2CADDR;
	messages[0].flags = 0;
	messages[0].len = sizeof(buff);
	messages[0].buf = buff;

	packets.msgs = messages;
	packets.nmsgs = 1;
																									 
	retVal = ioctl(file, I2C_RDWR, &packets);

	if(retVal < 0)
		perror("Write to I2C Device failed");

	return retVal;
}

void led_init(int data_min, int data_max) {

	char *filename = "/dev/i2c-1";
	int addr = I2CADDR;

	dmin = data_min;
	dmax = data_max;

	if ((file = open(filename, O_RDWR)) < 0) {
      /* ERROR HANDLING: you can check errno to see what went wrong */
      perror("Failed to open the i2c bus");
      exit(1);
	}
	
	if (ioctl(file, I2C_SLAVE, addr) < 0) {
				perror("Failed to acquire bus access and/or talk to slave");
				exit(1);
	}

	writeReg(PORTA_DD_REG_ADDR, 0x00);

}


/* Write a value to the leds */
void led_write(int value) {

  unsigned char out = 0;
	int i;

	// Convert to thermometer display
	value -= dmin;
	value *= 8;
	value /= (dmax-dmin);

	for(i = 0; i < value; i++) {

		out <<= 1;
		out |= 0x01;

	}

	printf("Binary: %08b\n", out);

	writeReg(PORTA_REG_ADDR, out);

}

