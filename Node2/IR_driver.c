#include "IR_driver.h"
#include <avr/io.h>

void ADC_initialize() {
    /*Enable ADC*/
    ADCSRA |= (1<<ADEN);

    /*Set ADC0 as input channel*/
    ADCSRB &= (1<<MUX5);
    ADMUX &= (1<<MUX4) & (1<<MUX3) & (1<<MUX2) & (1<<MUX1) & (1<<MUX0);
}