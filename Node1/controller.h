#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdint.h"


#endif
/**
 * Initialize input pins for analog controller input
*/
void controller_initialize();

/**
 * Send controller data over CAN bus
*/
void controller_CAN_send();