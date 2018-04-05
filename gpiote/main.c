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

// aktivere CHEN register
  PPI->CHENSET = 0x00000007;

  //forklare?
  PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[0]);
  PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[1]);
  PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[2]);

  while(1){
	}
	return 0;
}
