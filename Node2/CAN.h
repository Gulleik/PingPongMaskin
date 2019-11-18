#ifndef CAN_H
#define CAN_H

#define STATE_IDLE 0
#define STATE_PLAY 1

#include <avr/interrupt.h>
#include "MCP.h"

/**
 * @file
 * @brief Can driver NODE2
*/

/** 
 * @brief CAN message 
 */
struct message_t {
    uint16_t ID;
    uint8_t data[8];
    uint8_t length;
} typedef message_t; 

/**
 * @brief Different message IDs 
 */
enum MESSAGE_ID {
	NODE2_STATE, CONFIG, CONTROLS, SCORE
};

/**
 * @brief Different button types 
 */
enum BUTTON {
    UNDEF, JOYSTICK, LEFT, RIGHT, BOTH
};

volatile message_t node2_state_msg; /** < @brief message to keep track of node 2 state */
volatile message_t config_msg; /** < @brief message to keep track of controller configurations */
volatile message_t controls_msg; /** < @brief message to keep track of the controll inputs */
volatile message_t score_msg; /** < @brief message to keep track of score */

/**
 * @brief Initialize can driver
*/
void CAN_initialize();

/**
 * @brief Write message over the Can bus
   @param msg; message to be sent.
*/
void CAN_write_message(message_t msg);

/**
 * @brief Receive message over the Can bus
   @param msg; message to be sent.
*/
void CAN_receive_message();

#endif