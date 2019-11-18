#include "solenoid.h"

void solenoid_initialize(){
    DDRB |= (1 << PH5);
}

void solenoid_shoot(){
    PORTB &= ~(1 << PB5);
    _delay_ms(150);
    PORTB |= 1<<PB5;
}