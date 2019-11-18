#ifndef OLED_interface_H
#define OLED_interface_H

#define REDRAW_SCREEN 1
#define RETAIN_SCREEN 0

#define F_CPU 4915200 // clock frequency in Hz

#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include "controller.h"
#include "OLED.h"

/**
 * @file
 * @brief Oled interface driver
*/

/**
 * @brief Initialize all modules that the OLED FSM relies on, and configure node2 to default values.
 * @param refresh_rate; Specifies refresh rate of OLED screen, used in OLED initialization
*/
void OLED_FSM_initialize(uint8_t refresh_rate);

/**
 * @brief Run FSM for human interaction over OLED screen. Includes FSM for system operation
*/
void OLED_FSM_run();

#endif
