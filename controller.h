#ifndef CONTROLLER_H
#define CONTROLLER_H


#endif
/**
 * Read USB multifunction joystick value in X-direction, and convert to [-100,100]
 * @return converted joystick value
*/
char controller_joystick_read_X(); //returns value between -100 and 100

/**
 * Read USB multifunction joystick value in Y-direction, and convert to [-100,100]
 * @return converted joystick value
*/
char controller_joystick_read_Y(); //returns value between -100 and 100

/**
 * Read USB multifunction left slider value, and convert to [-100,100]
 * @return converted slider value
*/
char controller_slider_read_L(); //returns value between 0 and 100

/**
 * Read USB multifunction right slider value, and convert to [-100,100]
 * @return converted slider value
*/
char controller_slider_read_R(); //returns value between 0 and 100

/**
 * Read USB multifunction button value
 * @return button: ascii values of l, r, or b corresponding to left, right, both.
*/
char controller_button_read();

