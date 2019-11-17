#include "OLED_refresh.h"
#include "CAN.h"
#include "OLED.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>

void OLED_refresh_initialize(uint8_t refresh_rate) {
    /*
    Clock frequency is 4 915 200 Hz
    =>   Prescaler = 1    : 4 915 200 Hz
    =>   Prescaler = 8    : 614 400 Hz
    =>   Prescaler = 64   : 76 800 Hz
    =>   Prescaler = 256  : 19 200 Hz
    =>   Prescaler = 1024 : 4 800 Hz
    */

    /**********************************************************
     * INITIALIZE TIMER
    **********************************************************/
    /*Set mode of operation to CTC, where TOP is set by OCRnA*/
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);

    /*Set normal port operation, OC1A/OC1B disconnected*/
    TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0)
              | (1 << COM1B1) | (1 << COM1B0));

    /*Set prescaler to 256*/
    TCCR1B &= ~((1 << CS11 | 1 << CS10));
    TCCR1B |= (1 << CS12);

    /*Set TOP for output compare port A to match requested refresh rate*/
    uint16_t TOP = 19200 / refresh_rate;
    OCR1AH = ((TOP >> 8) & 0xFF);
    OCR1AL = (TOP & 0xFF);

    /*Interrupt configuration*/
    TIMSK = (1 << OCIE1A) //Enable interrupt on compare match at compare port A
            | (1 << TOIE1); //Enable interrupt on timer overflow

    /*Initially disable interrupt*/
    TIMSK &= ~(1 << OCIE1A);

    /*Enable global interrupts in case this has not been done already*/
    sei();
}

void OLED_refresh_enable() {
    /*Enable timer by enabling interrupts*/
    TIMSK |= (1 << OCIE1A);
}

void OLED_freeze_image() {
    /*Disable timer by disabling interrupts*/
    TIMSK &= ~(1 << OCIE1A);
}

ISR (TIMER1_COMPA_vect) {
    OLED_update_image();
}

ISR (TIMER1_OVF_vect) {
    
}