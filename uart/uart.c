#include <stdint.h>
#include "uart.h"
#include "gpio.h"

void uart_init(){
	GPIO->DIRSET = (1 << 24);	//TXD set to output
	GPIO->DIRCLR = (1 << 25); 	//RXD set to input
	
	UART->PSELTXD &= !(1 << 24); 	//pin select for TxD UART 
	UART->PSELRXD &= !(1 << 25); 	//pin select for RxD UART

	//er dette riktig
	UART->BAUDRATE = 0x00275000;	//Set baudrate to 9600 baud
	UART->CTS = 0xFFFFFFFF;
	UART->NRTS = 0xFFFFFFFF;
	UART->CONFIG = 0;


	UART->ENABLE = 4; //enable uart
	//UART->STARTTX = 1; //enable uart receiver
	UART->STARTRX = 1; //enable uart transmitter
};


void uart_send(char letter){
	UART->STARTTX = 1;	//?
	UART->TXD = letter;

	while(!(UART->TXDRDY)){
	}

	UART->STOPTX = 1;
	UART->STARTTX = 0;		//start og stop samme?
	UART->TXDRDY = 0;

};
char uart_read(){

	UART->STARTRX = 1;

	if(UART->RXDRDY){
		UART->RXDRDY = 0;
		return UART->RXD;

	}
	UART->STARTRX = 0;
	return '\0';
};



