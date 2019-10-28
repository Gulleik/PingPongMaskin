#include "IR_driver.h"
#include <avr/io.h>
//#include <stdint.h>

void IR_internal_ADC_init() {
    /*Enable ADC*/
    ADCSRA |= (1<<ADEN);

    /*Set ADC0 as input channel*/
    ADCSRB &= (1<<MUX5);
    ADMUX &= (1<<MUX4) & (1<<MUX3) & (1<<MUX2) & (1<<MUX1) & (1<<MUX0);

    /*Set left adjustment, only 8 bit precition is required*/
    ADMUX |= (1<<ADLAR);
}

uint8_t IR_internal_ADC_read() {
    /*Set ADSC bit to start conversion*/
    ADCSRA |= (1<<ADSC);
    
    /*Return digitally converted analog signal, with precition of 8 bits*/
    return ADCH;
}

uint8_t IR_is_blocked() {
    return !(IR_internal_ADC_read() > 0xAF);
}