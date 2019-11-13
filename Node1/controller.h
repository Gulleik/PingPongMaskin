#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdint.h"


/**
 * @brief Initialize input pins for analog controller input
*/
void controller_initialize();

/**
 *  @brief Send controller data over CAN bus
*/
void controller_CAN_send();

#endif