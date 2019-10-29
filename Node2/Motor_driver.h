
#include <stdint.h>

void motor_driver_set_dir(uint8_t joy_pos);

void motor_driver_enable_motor();

void motor_driver_disable_motor();

void motor_driver_run(uint8_t joy_pos);