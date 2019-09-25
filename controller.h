#ifndef CONTROLLER_H
#define CONTROLLER_H


#endif
char controller_joystick_read_X(); //returns value between -100 and 100

char controller_joystick_read_Y(); //returns value between -100 and 100

char controller_slider_read_L(); //returns value between 0 and 100

char controller_slider_read_R(); //returns value between 0 and 100

char controller_button_read(); //returns the ascii values of l, r, or b for left right or both. j for joystick pressed down. 0 else