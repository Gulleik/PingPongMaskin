#define F_CPU 16000000 // clock frequency in Hz

#define F_CPU 16000000 // clock frequency in Hz
#include "solenoid.h"
#include <util/delay.h>

void solenoid_init(){
    DDRB |= (1 << PH5);
}

void solenoid_shoot(){
    PORTB &= ~(1 << PB5);
    _delay_ms(150);
    PORTB |= 1<<PB5;
}