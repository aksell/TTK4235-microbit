#include <stdio.h>
#define TWI0 ((NRF_TWI_REG*)0x40003000)

typedef struct {
    volatile uint32_t STARTRX;
    [...]
} NRF_TWI_REG;


void twi_init();
