#include "timer.h"

void timer_initialize(uint8_t refresh_rate) {
    /*
    Clock frequency is 4 915 200 Hz
    =>   Prescaler = 1    : 4 915 200 Hz    - 
    =>   Prescaler = 8    : 614 400 Hz      - 
    =>   Prescaler = 64   : 76 800 Hz       - 
    =>   Prescaler = 256  : 19 200 Hz       - Resolution ~52us, Max 3,4s
    =>   Prescaler = 1024 : 4 800 Hz        - Resolution ~0,2ms, Max ~13,65s
    */

    /**********************************************************
     * INITIALIZE OLED TIMER [1]
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
    TIMSK |= (1 << OCIE1A) //Enable interrupt on compare match at compare port A
            | (1 << TOIE1); //Enable interrupt on timer overflow

    /*Initially disable interrupt*/
    TIMSK &= ~(1 << OCIE1A);

    
    /**********************************************************
     * INITIALIZE GAME TIMER [3]
    **********************************************************/
    time = 0; //Initialize at 0s
    /*Set mode of operation to CTC, where TOP is set by OCRnA*/
    TCCR3A &= ~((1 << WGM31) | (1 << WGM30));
    TCCR3B |= (1 << WGM32);
    TCCR3B &= ~(1 << WGM33);

    /*Set normal port operation, OC1A/OC1B disconnected*/
    TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0)
              | (1 << COM3B1) | (1 << COM3B0));

    /*Set prescaler to 256*/
    TCCR3B &= ~((1 << CS31 | 1 << CS30));
    TCCR3B |= (1 << CS32);

    /*Set TOP for output compare port A to 0d19200 = 0x4B00 => Int every 1s*/
    OCR3AH = 0x4B;
    OCR3AL = 0x00;

    /*Interrupt configuration*/
    ETIMSK |= (1 << OCIE3A) //Enable interrupt on compare match at compare port A
            | (1 << TOIE3); //Enable interrupt on timer overflow

    /*Initially disable interrupt*/
    ETIMSK &= ~(1 << OCIE3A);

    /*Enable global interrupts in case this has not been done already*/
    sei();
}

void timer_game_enable() {
    /*Enable game timer by enabling interrupts*/
    ETIMSK |= (1 << OCIE3A);
}

void timer_game_disable() {
    /*Disable game timer by disabling interrupts*/
    ETIMSK &= ~(1 << OCIE3A);
}

ISR (TIMER3_COMPA_vect) {
	//Game timer, activates every 1s
    time++;
}

ISR (TIMER3_OVF_vect) {
    
}