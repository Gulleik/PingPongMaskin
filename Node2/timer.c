#include "timer.h"
#include <avr/io.h>

void timer_initialize() {
    /*Initialize timer 3 as controller update timer*/
    /*Start TC module 3*/
    PRR1 |= ~(1 << PRTIM3);

    /*Set mode of operation to CTC, where TOP is set by OCRnA*/
    TCCR3A &= ~((1 << WGM31) | (1 << WGM30));
    TCCR3B |= ~(1 << WGM32);
    TCCR3B = ~(1 << WGM33);
    /*Set normal port operation, OC3A/OC3B/OC3C disconnected*/
    TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0)
              | (1 << COM3B1) | (1 << COM3B0)
              | (1 << COM3C1) | (1 << COM3C0));

    /*Set prescaler to divide by 8*/
    TCCR3B |= (0 << CS12 | 1 << CS11 | 0 << CS10);

    /*Set TOP for output compare port A*/
    OCR3AH = 0x00;
    OCR3AL = 0xFF;

    /*Interrupt configuration*/
    TIMSK3 = (1 << OCIE3A) //Enable interrupt on compare match at compare port A
           | (1 << ICIE3); //Enable interrupt on timer overflow
    sei();
}

ISR (TIMER3_COMPA) {
    printf("Timer says helo\n\r");
}

ISR (TIMER3_OVF_VECT) {
    printf("Timer 3 overflow\n\r");
}