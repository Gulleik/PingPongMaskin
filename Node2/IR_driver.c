#include "IR_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdint.h>

void IR_internal_ADC_init() {
    /*Enable ADC*/
    ADCSRA |= (1<<ADEN);
    /*Enable interrupt on completed conversion and set global interrupt flag*/
    ADCSRA |= (1<<ADIE);
    sei();

    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    /*Set ADC0 as input channel*/
    ADCSRB &= ~(1<<MUX5);
    ADMUX &= ~((1<<MUX4) |(1<<MUX3) | (1<<MUX2) | (1<<MUX1));// & (1<<MUX0);
    ADMUX |= (1<<MUX0);
    /*Set AVCC as voltage reference, with external cap. at AREF*/
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << REFS0);
    //ADMUX |= (1 << REFS0);

    /*Set left adjustment, only 8 bit precition is required*/
    ADMUX |= (1<<ADLAR);
}

void IR_internal_ADC_read() {
    
    ADCSRA |= (1<<ADSC);

    /*Busy wait for completed conversion*/
    //while (!(ADCSRA << ADIF)); //REDUNDANT WITH ISR
    
    /*Return digitally converted analog signal, with precition of 8 bits*/
    //return ADCH; //REDUNDANT WITH ISR
}

ISR(ADC_vect) {
    cli();
    /*Check digitally converted analog signal against constant treshold*/
    uint8_t temp = ADCH;
    printf("ADCH: %d\n\r", temp);
    is_blocked = !(temp > 5);
    sei();
}