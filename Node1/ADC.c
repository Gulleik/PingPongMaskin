#define F_CPU 4915200

#include "ADC.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t *ext_ADC = (char *) 0x1400;

char ADC_read(uint8_t *channel){
    /*Write configuration to MUX-pins, Y-axis to CH1*/
    ext_ADC[0] = channel;
    
    /*Wait for stable digital output*/
    _delay_us(30);
    
    return ext_ADC[0];
}