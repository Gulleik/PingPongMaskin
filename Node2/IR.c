#include "IR.h"

void IR_internal_ADC_initialize() {
    /*Enable ADC*/
    ADCSRA |= (1<<ADEN);
    /*Enable interrupt on completed conversion and set global interrupt flag*/
    ADCSRA |= (1<<ADIE);
    sei();

    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    /*Set ADC1 as input channel*/
    ADCSRB &= ~(1<<MUX5);
    ADMUX &= ~((1<<MUX4) |(1<<MUX3) | (1<<MUX2) | (1<<MUX1));// & (1<<MUX0);
    ADMUX |= (1<<MUX0);
    /*Set AVCC as voltage reference, with external cap. at AREF*/
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << REFS0);

    /*Set left adjustment, only 8 bit precition is required*/
    ADMUX |= (1<<ADLAR);

    /*initialize CAN*/
    CAN_initialize();
    
}

void IR_internal_ADC_read() {
    
    /*Start Conversion*/
    ADCSRA |= (1<<ADSC);

    /*Busy wait for completed conversion*/
    //while (!(ADCSRA << ADIF)); //REDUNDANT WITH ISR
    
    /*Return digitally converted analog signal, with precition of 8 bits*/
    //return ADCH; //REDUNDANT WITH ISR
}

uint8_t reset = 1;

ISR(ADC_vect) {
    cli();
    /*Check digitally converted analog signal against constant treshold*/
    uint8_t temp = ADCH;
    if( temp > 50){
        reset = 1;
    }
    
    if(!(temp > 30) && reset){
        CAN_write_message(score_msg);
        reset = 0;
    }; //Min: 0, Max: 255
    sei();
}