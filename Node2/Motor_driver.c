#include "Motor_driver.h"
#include <avr/io.h>
#include <stdint.h>

void motor_driver_set_dir(uint8_t joy_pos){
    DDRH = 1;
    if (joy_pos > 130){
        PORTH |= (1 << PH1);
    }else{
        PORTH |= (0 << PH1);
    }
}

void motor_driver_enable_motor(){
    DDRH = 1;
    PORTH |= (1 << PH4);
}

void motor_driver_disable_motor(){
    DDRH = 1;
    PORTH |= (1 << PH4);
}

void motor_driver_run(uint8_t joy_pos){
    if( joy_pos != 130 && joy_pos != 131){
        motor_driver_set_dir(joy_pos);
        motor_driver_enable_motor();
    }else{
        motor_driver_disable_motor();
    }
}