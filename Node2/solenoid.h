#ifndef SOLENOID_H
#define SOLENOID_H

#include <avr/io.h>

/**
 * @brief Initialize solenoid
*/
void solenoid_initialize();

/**
 * @brief Send a pulse through the solenoid
*/
void solenoid_pulse();

#endif