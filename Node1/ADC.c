#include "ADC.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t ADC_status = 0;
volatile uint8_t ADC_val = 0;
volatile char *ext_ADC = (char *) 0x1400;

void ADC_init(){
    /* enable interrupts on falling edge*/
    MCUCR |= (1 << ISC11);
    /* enables interrupts*/
    GICR |= (1 << INT1);
}

char ADC_read(char *channel){
    ext_ADC[0] = channel; //Write configuration to MUX-pins, Y-axis to CH1
    return ADC_val;
}

ISR (INT1_vect) {
    ADC_val = ext_ADC[0];
}