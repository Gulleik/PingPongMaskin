#include "servo_driver.h"
#include <avr/interrupt.h>

//RANGE: 1800 - 4200, 3000 median
uint16_t servo_pos = 3000;

void servo_driver_pwm_init(){
    //start TC module
    PRR0 &= ~(1 << PRTIM1);

    DDRB |= (1 << PB6);
    // set fast pwm where top is set by OCRn
    TCCR1A |= (0 << COM1B0 | 1 << COM1B1 | 1 << WGM11 | 0 << WGM10);
    TCCR1B |= (0 << CS12 | 1 << CS11 | 0 << CS10 | 1 << WGM13 | 1 << WGM12);

    //set top
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

void servo_driver_pwm_controller(uint8_t pos){
    servo_pos = 1800 + ((pos*120)/13);
    OCR1A = servo_pos;
}


ISR (TIMER1_OVF_vect){
	OCR1B = servo_pos;
}