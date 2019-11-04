#include <avr/io.h>

#define FREC 

/**
 * Initialises the Servo, enables fast pwm, overflow interupts, and sets prescaler to divide by 8
*/
void Servo_initialize();

/**
 * Sets servo position
 * @param pos; Desired position of encoder, value between 0 and 255.
*/
void Servo_set_position(uint8_t pos);