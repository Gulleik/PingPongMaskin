
#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>


#include <util/delay.h>
#define MOTOR_RIGHT 0
#define MOTOR_LEFT 1

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6


uint16_t curr_pos;

void motor_driver_initialise();

void motor_driver_reset_encoder();

void motor_driver_calibrate();

void motor_driver_set_dir(uint8_t dir);

void motor_driver_enable_motor();

void motor_driver_update_slider_ref(uint8_t slider_pos);

void motor_driver_disable_motor();

void motor_driver_run(uint8_t joy_pos);

void motor_driver_encoder_enable();

void motor_driver_encoder_disable();

uint16_t motor_driver_encoder_read_byte();

void motor_driver_adjust_speed(uint8_t speed);

uint8_t motor_driver_calculate_ref_speed(unsigned char pos);

void motor_driver_update_ref(uint8_t joy_pos);

void motor_driver_update_pos();

#endif