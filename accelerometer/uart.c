#include <stdint.h>
#include "uart.h"
#include "gpio.h"

void uart_init(){
	GPIO->DIRSET = (1 << 24);	//TXD set to output
	GPIO->DIRCLR = (1 << 25); 	//RXD set to input
	
	UART->PSELTXD = 24; 	//pin select for TxD UART 
	UART->PSELRXD = 25; 	//pin select for RxD UART

	//er dette riktig
	UART->BAUDRATE = 0x00275000;	//Set baudrate to 9600 baud
	UART->PSELRTS = 0xFFFFFFFF;
	UART->PSELCTS = 0xFFFFFFFF;
	UART->CONFIG = 0;


	UART->ENABLE = 4; //enable uart
	UART->STARTRX = 1; //enable uart transmitter
};


void uart_send(char letter){
	UART->STARTTX = 1;
	UART->TXD = letter;

	while(!(UART->TXDRDY)){
	}
	UART->TXDRDY = 0;
	UART->STOPTX = 1;

};
char uart_read(){
	if(UART->RXDRDY){
		char letter = UART->RXD;
		UART->RXDRDY = 0;
		return letter;
	}
	return '\0';
};



