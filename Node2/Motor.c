#define F_CPU 16000000 // clock frequency in Hz

#include "Motor.h"
#include "CAN.h"
#include "TWI_Master.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t MAX_pos;
uint16_t MIN_pos;
int16_t i_error = 0;
int16_t d_error = 0;
int16_t previos_error = 0;
uint16_t K_p;   //DEFAULT 80
uint16_t K_i;   //DEFAULT 10
uint16_t K_d;   //DEFAULT 100

// Max speed a value between 0 and 255
uint8_t Max_speed; //DEFAULT 120

void Motor_reset_encoder(){
    PORTH &= ~(1 << RST); //resetting encoder pos
    _delay_us(30);
    PORTH |= (1 << RST); // --||--
}

void Motor_set_dir(uint8_t dir){
    if (dir == 0){
        PORTH |= (1 << DIR); // høgre
    }else{
        PORTH &= ~(1 << DIR); // venstre
    }
}

uint16_t Motor_encoder_read_data(){
    /*Enable encoder*/
    PORTH &= ~(1 << OE);
    uint16_t data;

    /*Read high Byte of signal*/
    PORTH &= ~(1 << SEL); //Set SEL low to get high byte
    _delay_ms(20);
    data = (PINK << 0x8);

    /*Read low Byte of signal*/
    PORTH |= (1 << SEL); //Set SEL high to get low byte
    _delay_ms(20);
    data |= PINK;
    /*Disable encoder*/
    PORTH |= (1 << OE);
    return data;
}

void Motor_adjust_speed(uint8_t speed){
    unsigned char msg[3];
    msg[0] = 0b01010000;
    msg[1] = 0;
    if (speed > Max_speed){
        speed = Max_speed;
    }
    msg[2] = speed;
    TWI_Start_Transceiver_With_Data(msg,3);
}

void Motor_initialise(){
    printf("Motor initializing...\n\r");
    TWI_Master_Initialise();
    position_ref = 0;
    DDRH = 0xFF;
    DDRK = 0x00;
    Motor_enable_motor(ON);
    //Motor_calibrate();
}

void Motor_calibrate(){
    printf("Motor calibrating...\n\r");

    Motor_set_dir(MOTOR_RIGHT);
	Motor_adjust_speed(80);
	_delay_ms(1000);

    /*Log right encoder position*/
	Motor_adjust_speed(0);
    _delay_ms(100);
	Motor_reset_encoder();
	MIN_pos = Motor_encoder_read_data();
	
	Motor_set_dir(MOTOR_LEFT);
	Motor_adjust_speed(80);
	_delay_ms(1000);

    /*Log left encoder position*/
	Motor_adjust_speed(0);
    _delay_ms(100);
	MAX_pos = Motor_encoder_read_data();

	printf("Motor is calibrated, min_pos: %d\tmax_pos: %d\n\r", MIN_pos, MAX_pos);
}

void Motor_enable_motor(uint8_t state){
    if (state){
        printf("Enabling\n\r");
        PORTH |= (1 << EN);
    }else{
        PORTH &= ~(1 << EN);
    }
}

void Motor_update_slider_ref(uint8_t slider_pos){
    float scale = (float)(MAX_pos-MIN_pos)/255;
    position_ref = MAX_pos - scale*((uint16_t) slider_pos);
}

void Motor_position_controller(){
    /*Get config data*/
    K_p = config_msg.data[1]; //1 = Data pos for K_p
    K_i = config_msg.data[2]; //2 = Data pos for K_i
    K_d = config_msg.data[3]; //3 = Data pos for K_d
    Max_speed = config_msg.data[0];

    int16_t e = (position_ref - Motor_encoder_read_data());
    e = e/100;
    i_error += e;
    d_error = -e + previos_error;
    int16_t u = e*K_p + i_error*K_i - K_d*d_error;
    if( u < 0 ){
        Motor_set_dir(MOTOR_RIGHT);
    }else{
        Motor_set_dir(MOTOR_LEFT);
    }
    u = u/50;
    u = abs(u);
    if (u > Max_speed){
        u = Max_speed;
    }
    Motor_adjust_speed(u);
    previos_error = e;
}

/*
uint8_t Motor_calculate_ref_speed(unsigned char pos){
    if(pos < 131){
        return (131-pos)*(248/131);
    }else{
        return 2*(pos-131);
    }
}

void motor_update_joystic_ref(uint8_t joy_pos){
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
    //printf("curr_pos = %d\t\t", curr_pos);
}*/