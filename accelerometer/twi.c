#include "twi.h"



//akiver TWI mod m- riktige signalinjene og 100kbps, signallinjer pmå akriveres av GPIO
void twi_init(){
    GPIO->CNF[0] = (1<<3)|(1<<2)|(1<<9)|(1<<10);// SCL ->input, activate pullup, drive stength S0D1
    GPIO->CNF[30] = (1<<3)|(1<<2)|(1<<9)|(1<<10);// SDA ->input, activate pullup, drive stength S0D1

    TWI0->STARTTX = 0;
    TWI0->STARTRX = 0;

    TWI0->ENABLE = 5; //Enable TWI

    TWI0->FREQUENCY = 0x01980000; // 100kbps

    TWI0->ADDRESS = 0; //clear slave address register

    //Clear all registers
    TWI0->TXDSENT = 0;
    TWI0->RXDREADY = 0;
    TWI0->ERROR = 0;
}

void twi_multi_read(uint8_t slave_address,uint8_t start_register,
                    int registers_to_read,uint8_t * data_buffer){
    TWI0->ADDRESS = slave_address; //set slave address
    TWI0->STARTTX = 1; //start a write operation


    TWI0->TXDSENT = 0;
    TWI0->TXD = start_register; //put start register on TWI bus
    while(!TWI0->TXDSENT); //wait for a ACK that the transmit is done

    TWI0->RXDREADY = 0;//the microcontroller does not reset flags after task is done, we have to
    TWI0->STARTRX = 1;
    for(int i = 0; i < (registers_to_read -1);i++){
        while(!TWI0->RXDREADY); //wait for a ACK , byte received
        data_buffer[i] = TWI0->RXD;

        TWI0->RXDREADY = 0; //Reset ACK for byte received
    }

    TWI0->STOP = 1;//start the STOP task, to give a NACK, this stops the slave
    data_buffer[registers_to_read -1] = TWI0->RXD; //read buss one last time

    TWI0->RXDREADY = 0;
    //TWI0->STARTRX = 1;

}
