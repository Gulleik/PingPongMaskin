#include "Servo.h"
#include <avr/interrupt.h>

//RANGE: 1800 - 4200, 3000 median
uint16_t servo_pos = 3000;

void Servo_initialize(){
    //start TC module
    PRR0 &= ~(1 << PRTIM1);

    DDRB |= (1 << PB6);
    // set non-inverting fast pwm where top is set by OCRn
    //TCCR1A |= (1 << COM1B1 | 0 << COM1B0 | 1 << WGM11 | 0 << WGM10);
    TCCR1A |= ((1 << COM1B1) | (1 << WGM11));
    TCCR1A &= ~((1 << COM1B0) | (1 << WGM10));
    // set prescaler to divide by 8
    //TCCR1B |= (0 << CS12 | 1 << CS11 | 0 << CS10 | 1 << WGM13 | 1 << WGM12);
    TCCR1B |= ((1 << CS11) | (1 << WGM13) | (1 << WGM12));
    TCCR1B &= ~((1 << CS12) | (1 << CS10));

    //set top aka period
    ICR1H = 0x9C;
    ICR1L = 0x3F;
    OCR1A = servo_pos;

    cli();
    

    TIMSK1 = 0 << OCIE1B   /* Output Compare B Match Interrupt Enable: disabled */
	        | 0 << OCIE1A /* Output Compare A Match Interrupt Enable: disabled */
	        | 0 << ICIE1  /* Input Capture Interrupt Enable: disabled */
	        | 1 << TOIE1; /* Overflow Interrupt Enable: enabled */

    sei();

}

void Servo_set_position(uint8_t pos, uint8_t inverted){
    if (inverted) {
        servo_pos = 4200 - ((pos*120)/13);
    } else {
        servo_pos = 1800 + ((pos*120)/13);
    }
    OCR1A = servo_pos;
}

ISR (TIMER1_OVF_vect){
	OCR1B = servo_pos;
}