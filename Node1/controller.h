#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdint.h"


#endif
/**
 * Initialize input pins for analog controller input
*/
void controller_initialize();

/**
 * Read USB multifunction joystick value in X-direction, and convert to [-100,100]
 * @return converted joystick value
*/
uint8_t controller_joystick_read_X(); //returns value between 0 and 255

/**
 * Read USB multifunction joystick value in Y-direction, and convert to 0 and 255
 * @return converted joystick value
*/
uint8_t controller_joystick_read_Y(); //returns value between 0 and 255

/**
 * Read USB multifunction left slider value, and convert to [-100,100]
 * @return converted slider value
*/
uint8_t controller_slider_read_L(); //returns value between 0 and 100

/**
 * Read USB multifunction right slider value, and convert to [-100,100]
 * @return converted slider value
*/
uint8_t controller_slider_read_R(); //returns value between 0 and 100

/**
 * Read USB multifunction button value
 * @return button
*/
uint8_t controller_button_read(); //returns the ascii values of l, r, or b for left right or both

void controller_CAN_send();