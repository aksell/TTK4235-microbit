#include <stdio.h>
#include <stdint.h> //needed?
#include "twi.h"
#include "utility.h"
#include "uart.h"
#include "accel.h"
#include "ubit_led_matrix.h"

int main(){
	twi_init();
	uart_init();
	utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", 1, 2, 3);
	accel_init(); 
	utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", 1, 2, 3);

	ubit_led_matrix_init();

	int * coordinates = (int *)malloc(3 * sizeof(int));

	while(1){

		accel_read_x_y_z(coordinates);

		int x_acc = coordinates[0];
		int y_acc = coordinates[1];
		int z_acc = coordinates[2];
		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);

		int x_dot = x_acc / 50;
		int y_dot = - y_acc / 50;

		ubit_led_matrix_light_only_at(x_dot, y_dot);
		
		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);


	};







	/* OPPGAVE 6.5
	utility_print(&uart_send, "Hei!\n\r");
	//uint8_t WHO_AM_I_ACCEL_VALUE = 0x5A; //acelerometer device address, for reference
	uint8_t WHO_AM_I_ACCEL_ADR = 0x0D; //address where WHO_AM_I is stored

	uint8_t accel_addres = 0x1D; //accelerometer slave address

	uint8_t register_to_read = 3;
	uint8_t * data_buffer;
	utility_print(&uart_send, "Num: %d\n\r", 42);
	data_buffer = (uint8_t *)malloc(8 * sizeof(uint8_t));

	twi_multi_read(accel_addres, WHO_AM_I_ACCEL_ADR, register_to_read, data_buffer);

	utility_print(&uart_send, "Num: %d\n\r", data_buffer[1]);//write address over uart. takes only whole number does no error checking

	free(data_buffer);

	*/

	free(coordinates);





	return 0;
}

// /r is carriage return