
#include <stdint.h>
#include "ppi.h"
#include "utility.h"
#include "pwm.h"
#include "timer.h"
#include "accel.h"
#include "ubit_led_matrix.h"
#include "uart.h"
#include "twi.h"

int main(){
	twi_init();
	uart_init();
	utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", 1, 2, 3);
	accel_init(); 
	utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", 1, 2, 3);

	ubit_led_matrix_init();

	pwm_init(3, 40000, 3000);

	int * coordinates = (int *)malloc(3 * sizeof(int));

	while(1){

		accel_read_x_y_z(coordinates);

		int x_acc = coordinates[0];
		int y_acc = coordinates[1];
		int z_acc = coordinates[2];
		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);

		int x_dot = x_acc / 50;
		int y_dot = - y_acc / 50;

		int dd = 3000+x_acc*1000/256;
		
		if(dd>4000){
			dd=4000;
		}else if(dd <2000){
			dd=2000;
		}

		pwm_set_ticks(dd);



		ubit_led_matrix_light_only_at(x_dot, y_dot);
		
		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);


	};


	free(coordinates);
	return 0;

}

