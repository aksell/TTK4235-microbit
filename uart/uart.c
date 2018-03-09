#include <stdint.h>
#include "uart.h"
#include "gpio.h"

void uart_init(){
	GPIO->DIRSET = (1 << 24);	//TXD set to output
	GPIO->DIRCLR = (1 << 25); 	//RXD set to input
	
	UART->PSELTXD &= !(1 << 24); 	//pin select for TxD UART 
	UART->PSELRXD &= !(1 << 25); 	//pin select for RxD UART

	UART->ENABLE = 4; //enable uart
	//UART->STARTTX = 1; //enable uart receiver
	UART->STARTRX = 1; //enable uart transmitter
};


void uart_send(char letter){

	while(!(UART->TXDRY)){
		UART->TXD = letter;

	}


};
char uart_read();