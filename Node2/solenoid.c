#include "solenoid.h"

void solenoid_init(){
    DDRH |= (1 << PH5);
}

void solenoid_shoot(){
    PORTH |= 1<<PB5;
    //PORTB = 0 << PB5;
}