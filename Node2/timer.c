#include "timer.h"
#include "CAN.h"
#include <avr/io.h>
#include <avr/interrupt.h>



void timer_initialize() {
    /*
    Clock frequency is 16kHz
    =>   Prescaler = 1    : Resolution = 0,0625us,  Range = ~4ms
    =>   Prescaler = 8    : Resolution = 0,5us,   Range = ~32ms
    =>   Prescaler = 64   : Resolution = 4us,     Range = ~0,26s
    =>   Prescaler = 256  : Resolution = 16us,    Range = ~1s
    =>   Prescaler = 1024 : Resolution = 64us,    Range = ~4s
    */

    /**********************************************************
     * INITIALIZE CONTROLLER_TIMER
    **********************************************************/
    /*Set mode of operation to CTC, where TOP is set by OCRnA*/
    TCCR3A &= ~((1 << WGM31) | (1 << WGM30));
    TCCR3B |= (1 << WGM32);
    TCCR3B &= ~(1 << WGM33);

    /*Set normal port operation, OC3A/OC3B/OC3C disconnected*/
    TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0)
              | (1 << COM3B1) | (1 << COM3B0)
              | (1 << COM3C1) | (1 << COM3C0));

    /*Set prescaler to 64*/
    TCCR3B |= (1 << CS31 | 1 << CS30);
    TCCR3B &= ~(1 << CS32);

    /*Set TOP for output compare port A, 0x1388 => Int at 20ms*/
    OCR3AH = 0x13;
    OCR3AL = 0x88;

    /*Interrupt configuration*/
    TIMSK3 |= (1 << OCIE3A) //Enable interrupt on compare match at compare port A
           | (1 << ICIE3); //Enable interrupt on timer overflow
    
    /**********************************************************
     * INITIALIZE IR_ADC_TIMER
    **********************************************************/
    /*Set mode of operation to CTC, where TOP is set by OCRnA*/
    TCCR4A &= ~((1 << WGM41) | (1 << WGM40));
    TCCR4B |= (1 << WGM42);
    TCCR4B &= ~(1 << WGM43);

    /*Set normal port operation, OC3A/OC3B/OC3C disconnected*/
    TCCR4A &= ~((1 << COM4A1) | (1 << COM4A0)
              | (1 << COM4B1) | (1 << COM4B0)
              | (1 << COM4C1) | (1 << COM4C0));

    /*Set prescaler to 64*/
    TCCR4B |= (1 << CS41 | 1 << CS40);
    TCCR4B &= ~(1 << CS42);

    /*Set TOP for output compare port A, 0xC350 => Int at 200ms*/
    OCR4AH = 0xC3;
    OCR4AL = 0x50;

    /*Interrupt configuration*/
    TIMSK4 |= (1 << OCIE4A) //Enable interrupt on compare match at compare port A
           | (1 << ICIE4); //Enable interrupt on timer overflow

    /*Initially disable all timers*/
    PRR1 |= (1 << PRTIM3 | 1 << PRTIM4);

    /*Enable global interrupts in case this has not been done already*/
    sei();
}

void timer_enable(timer_t timer) {
    switch (timer) {
        case CONTROLLER_TIMER:
            PRR1 &= ~(1 << PRTIM3);
            break;
        case IR_ADC_TIMER:
            PRR1 &= ~(1 << PRTIM4);
            break;
        default:
            break;
    }
}

void timer_disable(timer_t timer) {
    switch (timer) {
        case CONTROLLER_TIMER:
            PRR1 |= (1 << PRTIM3);
            break;
        case IR_ADC_TIMER:
            PRR1 |= (1 << PRTIM4);
            break;
        default:
            break;
    }
}

ISR (TIMER3_COMPA_vect) {
    //Every 20ms
    timer_interrupt = 1;
}

ISR (TIMER3_OVF_vect) {
    
}

ISR (TIMER4_COMPA_vect) {
    //Every 200ms
    IR_interrupt = 1;
}

ISR (TIMER4_OVF_vect) {
    
} 