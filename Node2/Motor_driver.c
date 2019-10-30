#include "Motor_driver.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>


void motor_driver_initialise(){
    TWI_Master_Initialise();
    curr_pos = 0;
    DDRH = 0xFF;
    PORTH = (0 << PH6);
    PORTH = (1 << PH6);
}

void motor_driver_set_dir(uint8_t joy_pos){
    DDRH =  0xFF;
    if (joy_pos > 0){
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
/*
void motor_driver_run(uint8_t joy_pos){
    if( joy_pos != 132 && joy_pos != 131 && joy_pos != 130){
        uint8_t speed =  motor_driver_calculate_speed(joy_pos);
        motor_driver_adjust_speed(speed);
        motor_driver_set_dir(joy_pos);
        motor_driver_enable_motor();
    }else{
        motor_driver_disable_motor();
    }
}*/

void motor_driver_encoder_enable(){
    DDRH = 0xFF;
    PORTH = (0 << PH5);
}

void motor_driver_encoder_disable(){
    DDRH = 0xFF;
    PORTH = (1 << PH5);
}

uint16_t motor_driver_encoder_read_byte(){
    motor_driver_encoder_enable();
    uint16_t data;
    DDRH = 0xFF;
    PORTH = (0 << PH3);
    DDRK = 0xFF;
    data = (PORTF << 0x8);
    PORTH = (1 << PH3);
    data |= PORTF;
    motor_driver_encoder_disable();
    return data;
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

uint8_t motor_driver_calculate_ref_speed(unsigned char pos){
    if(pos < 131){
        return (131-pos)*(248/131);
    }else{
        return 2*(pos-131);
    }
}
volatile uint16_t MAX_pos = 1000;
void motor_driver_update_ref(uint8_t joy_pos){
    if (curr_pos > MAX_pos){
        curr_pos = MAX_pos;
    }
    if( joy_pos != 132 && joy_pos != 131 && joy_pos != 130){
        if(joy_pos < 130 && curr_pos > 0){
            if((curr_pos - motor_driver_calculate_ref_speed(joy_pos)) > MAX_pos){
                curr_pos = 0;
            }else{
                curr_pos -= motor_driver_calculate_ref_speed(joy_pos); 
            }
        }else if(curr_pos < MAX_pos && joy_pos > 132){
            if((curr_pos + motor_driver_calculate_ref_speed(joy_pos)) > MAX_pos){
                curr_pos = MAX_pos;
            }else{
                curr_pos += motor_driver_calculate_ref_speed(joy_pos); 
            }
        }
    }
    printf("curr_pos = %d\t\t", curr_pos);
}

void motor_driver_update_pos(){
    if (motor_driver_encoder_read_byte() != curr_pos){
        uint8_t e = curr_pos - motor_driver_encoder_read_byte();
        i_error += e;
        uint8_t val = e*K_p + i_error*K_i;
        motor_driver_set_dir(val);
        if (abs(val) > 255){
            val = 255;
        }
        motor_driver_adjust_speed(val);
        motor_driver_enable_motor();
    }else{
        motor_driver_disable_motor();
    }
    
}