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
 * @brief Show interface for human interaction over OLED screen. Includes FSM for system operation
*/
void OLED_interface();

#endif
