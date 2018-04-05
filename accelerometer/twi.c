#include "twi.h"

//akiver TWI mod m- riktige signalinjene og 100kbps, signallinjer pmå akriveres av GPIO
void twi_init(){
	GPIO->CNF[0] = (1<<3)|(1<<2); 	// set SCL to input, activate pullup
	GPIO->CNF[30] = (1 << 16); 	// set SDA to input



}
