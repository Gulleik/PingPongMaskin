
#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_RIGHT 0
#define MOTOR_LEFT 1
#define ON 1
#define OFF 0

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6

#include <stdint.h>

uint16_t position_ref;



/**
 * initialize Motor and TWI, turns motor on and calls calibration function
*/
void Motor_initialize();

/**
 * sets MAX_pos and Min_pos for the motor
*/
void Motor_calibrate();

/**
 * Turns the motor on and off
 * @param state; 1 for turning the motor on, and 0 for turning it off
*/
void Motor_enable_motor(uint8_t state);

/**
 * Updates the position refference, optimised for slider input.
 * @param slider_pos; slider position value between 0 and 255.
*/
void Motor_update_slider_ref(uint8_t slider_pos);

/**
 * The position controller, ensuring that the position follows the refference
*/
void Motor_position_controller();




/*
void Motor_update_joystick_ref(uint8_t joy_pos);

uint8_t Motor_calculate_ref_speed(unsigned char pos);
*/

#endif