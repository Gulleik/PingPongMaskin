#ifndef SOLENOID_H
#define SOLENOID_H

#define F_CPU 16000000 // clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>

/**
 * @file
 * @brief Solenoid driver
*/

/**
 * @brief Initialize solenoid
*/
void solenoid_initialize();

/**
 * @brief Send a pulse through the solenoid
*/
void solenoid_pulse();

#endif