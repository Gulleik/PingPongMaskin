#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @file
 * @brief NODE2 Servo driver
*/

/**
 * @brief Initialises the Servo, enables fast pwm, overflow interupts, and sets prescaler to divide by 8
*/
void Servo_initialize();

/**
 * @brief Sets servo position
 * @param pos; Desired position of encoder, value between 0 and 255.
 * @param inverted; Boolean value specifying whether the servo controls should be inverted or not
*/
void Servo_set_position(uint8_t pos, uint8_t inverted);

#endif