#include "Motor_driver.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>


void motor_driver_initialise(){
    TWI_Master_Initialise();
}

void motor_driver_set_dir(uint8_t joy_pos){
    DDRH =  0xFF;
    if (joy_pos > 130){
        PORTH = (1 << PH1);
    }else{
        PORTH = (0 << PH1);
    }
}

void motor_driver_enable_motor(){
    DDRH = 0xFF;
    PORTH = (1 << PH4);
}

void motor_driver_disable_motor(){
    DDRH = 0xFF;
    PORTH = (0 << PH4);
}

void motor_driver_run(uint8_t joy_pos){
    if( joy_pos != 132 && joy_pos != 131 && joy_pos != 130){
        motor_driver_set_dir(joy_pos);
        motor_driver_enable_motor();
    }else{
        motor_driver_disable_motor();
    }
}

void motor_driver_encoder_enable(){
    DDRH = 0xFF;
    PORTH = (0 << PH5);
}

void motor_driver_encoder_disenable(){
    DDRH = 0xFF;
    PORTH = (1 << PH5);
}

void motor_driver_encoder_read_byte(){
    uint16_t data;
    DDRH = 0xFF;
    PORTH = (0 << PH3); 
}

void motor_driver_adjust_speed(uint8_t speed){
    unsigned char *msg;
    msg[0] = 0b01010000;
    msg[1] = 0b00000000;
    msg[2] = speed;
    PORTD = ((1<<PD0) | (0<<PD1));
    TWI_Start_Transceiver_With_Data(msg,0x18);
    PORTD = ((1<<PD0) | (1<<PD1));
}

uint8_t motor_driver_calculate_speed(unsigned char pos){
    uint8_t speed = 2*abs((unsigned char)131-pos);
    return speed;
}
