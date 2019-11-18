
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

#define F_CPU 16000000 // clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include "TWI_Master.h"

/**
 * @file
 * @brief Motor driver
*/

uint16_t position_ref; /** < @brief position refference */

/**
 * @brief Initialize Motor and TWI, turns motor on and calls calibration function
*/
void Motor_initialize();

/**
 * @brief Sets MAX_pos and Min_pos for the motor
 * @param K_p_conf; K_p configuration sent from Node 1
 * @param K_i_conf; K_i configuration sent from Node 1
 * @param K_d_conf; K_d configuration sent from Node 1
 * @param max_speed_conf; max speed configuration sent from Node 1
*/
void Motor_calibrate(uint8_t max_speed_conf, uint8_t K_p_conf, uint8_t K_i_conf, uint8_t K_d_conf);

/**
 * @brief Turns the motor on and off
 * @param state; 1 for turning the motor on, and 0 for turning it off
*/
void Motor_enable_motor(uint8_t state);

/**
 * @brief Updates the position refference, optimised for slider input.
 * @param slider_pos; Slider position value between 0 and 255.
*/
void Motor_update_slider_ref(uint8_t slider_pos);

/**
 * @brief The position controller, ensuring that the position follows the refference
 * @param reference, the position refference, value between 0 and 255.
*/
void Motor_position_controller(uint8_t reference);

#endif