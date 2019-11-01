




#define F_CPU 16000000 // clock frequency in Hz

#include "Motor_driver.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include <stdlib.h>

uint16_t MAX_pos;
uint16_t MIN_pos;
int16_t i_error = 0;
int16_t d_error = 0;
int16_t previos_error = 0;
uint8_t Max_speed = 120;


void motor_driver_initialise(){
    printf("Motor initializing...\n\r");
    TWI_Master_Initialise();
    curr_pos = 0;
    DDRH = 0xFF;
    DDRK = 0x00;
    motor_driver_enable_motor();
    motor_driver_reset_encoder();
    motor_driver_calibrate();
}


void motor_driver_reset_encoder(){
    PORTH &= ~(1 << RST); //resetting encoder pos
    _delay_us(30);
    PORTH |= (1 << RST); // --||--
}

void motor_driver_calibrate(){
    printf("Motor calibrating...\n\r");

    motor_driver_set_dir(MOTOR_RIGHT);
	motor_driver_adjust_speed(80);
	_delay_ms(1000);
    /*Log right encoder position*/
	motor_driver_adjust_speed(0);
    _delay_ms(100);
	motor_driver_reset_encoder();
	MIN_pos = motor_driver_encoder_read_byte();
	
	motor_driver_set_dir(MOTOR_LEFT);
	motor_driver_adjust_speed(80);
	_delay_ms(1000);
    /*Log left encoder position*/
	motor_driver_adjust_speed(0);
    _delay_ms(100);
	MAX_pos = motor_driver_encoder_read_byte();

	printf("Motor is calibrated, min_pos: %d\tmax_pos: %d\n\r", MIN_pos, MAX_pos);
}

// if dir = 0 go right, else go left
void motor_driver_set_dir(uint8_t dir){
    if (dir == 0){
        PORTH |= (1 << DIR); // høgre
    }else{
        PORTH &= ~(1 << DIR); // venstre
    }
}

void motor_driver_enable_motor(){
    printf("Enabling\n\r");
    PORTH |= (1 << EN);
}

void motor_driver_disable_motor(){
    PORTH &= ~(1 << EN);
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
    PORTH &= ~(1 << OE);
}

void motor_driver_encoder_disable(){
    PORTH |= (1 << OE);
}

uint16_t motor_driver_encoder_read_byte(){
    motor_driver_encoder_enable();
    uint16_t data;

    PORTH &= ~(1 << PH3); //Set SEL low to get high byte
    _delay_ms(20);
    data = (PINK << 0x8);
    PORTH |= (1 << PH3); //Set SEL high to get low byte
    _delay_ms(20);
    data |= PINK;
    motor_driver_encoder_disable();
    return data;
}

void motor_driver_adjust_speed(uint8_t speed){
    unsigned char msg[3];
    msg[0] = 0b01010000;
    msg[1] = 0;
    if (speed > Max_speed){
        speed = Max_speed;
    }
    msg[2] = speed;
    TWI_Start_Transceiver_With_Data(msg,3);
}

uint8_t motor_driver_calculate_ref_speed(unsigned char pos){
    if(pos < 131){
        return (131-pos)*(248/131);
    }else{
        return 2*(pos-131);
    }
}
/*
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
    //printf("curr_pos = %d\t\t", curr_pos);
}*/

void motor_driver_update_slider_ref(uint8_t slider_pos){
    float scale = (float)(MAX_pos-MIN_pos)/255;
    curr_pos = MAX_pos - scale*((uint16_t) slider_pos);
    
}

uint16_t K_p = 80;
uint16_t K_i = 10;
uint16_t K_d = 100;
void motor_driver_update_pos(){
    int16_t e = (curr_pos - motor_driver_encoder_read_byte());
    e = e/100;
    printf("e = %d\t\t", e);
    i_error += e;
    d_error = -e + previos_error;
    int16_t u = e*K_p + i_error*K_i - K_d*d_error;
    if( u < 0 ){
        motor_driver_set_dir(MOTOR_RIGHT);
    }else{
        motor_driver_set_dir(MOTOR_LEFT);
    }
    u = u/50;
    u = abs(u);
    printf("e*K_p = %d\ti_error*K_i = %d\td_error*K_d = %d\tu:%d\t\t", e*K_p, i_error*K_i, d_error*K_d, u);
    if (u > Max_speed){
        u = Max_speed;
    }
    motor_driver_adjust_speed(u);
    previos_error = e;

}