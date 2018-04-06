#include <stdio.h>
#include <stdint.h> //needed?

#include "twi.h"
#include "utility.h"
#include "uart.h"

int main(){
	//accel_init(); //accel init requires that you implement twi_multi_read first, not needed
	//to read who_am_i
	uart_init();
	
	uint8_t WHO_AM_I_ACCEL_VALUE = 0x5A; //acelerometer device address
	uint8_t WHO_AM_I_ACCEL_ADR = 0x0D; //address where WHO_AM_I is stored

	uint8_t accel_addres = 0x1D; //accelerometer slave address

	uint8_t register_to_read = 1;
	uint8_t * data_buffer;
	data_buffer = (uint8_t *)malloc(8 * sizeof(uint8_t));

	twi_multi_read(accel_addres, WHO_AM_I_ACCEL_ADR, register_to_read, data_buffer);

	utility_print(&uart_send, "Num: %d\n\r", data_buffer[0]);//write address over uart. takes only whole number does no error checking
	//utility print can be used with many different mediums uart or a physical printre
	//use picocom to read uart

	free(data_buffer);


	return 0;
}

// /r is carriage return