#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(){
  // jordingspinnene til LED-matrisen konﬁgureres som output
  // og settes til logisk lave
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}


  // Configure GPIOTE channels for Voltage supplies
//Configure A button for event
//0x00DCBB0A
//pin nr. 17 er 11 i hex

GPIOTE->CONFIG[0] = 0x00021101;

//configure LED for toggle and task mode (PIN nr 13-15)
GPIOTE->CONFIG[1] = 0x00030D03;
GPIOTE->CONFIG[2] = 0x00030E03;
GPIOTE->CONFIG[3] = 0x00030F03;

// Husk˚a aktivere hver PPI-kanal. N˚ar de er konﬁgurert riktig, aktiveres de ved ˚a skrive til CHENSET i PPI-instansen.

  while(1){
	}
	return 0;
}
