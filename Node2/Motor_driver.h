
#include <stdint.h>

void motor_driver_initialise();

void motor_driver_set_dir(uint8_t joy_pos);

void motor_driver_enable_motor();

void motor_driver_disable_motor();

void motor_driver_run(uint8_t joy_pos);

void motor_driver_encoder_enable();

void motor_driver_encoder_disable();

void motor_driver_encoder_read_byte();

void motor_driver_adjust_speed(uint8_t speed);

uint8_t motor_driver_calculate_speed(unsigned char pos);