#ifndef CAN_H
#define CAN_H

#define STATE_IDLE 0
#define STATE_PLAY 1

#define CONF_DEFAULT_TOP_SPEED 120
#define CONF_DEFAULT_Kp 80
#define CONF_DEFAULT_Ki 10
#define CONF_DEFAULT_Kd 100
#define CONF_DEFAULT_INV_SERVO 0
#define CONF_DEFAULT_INV_MOTOR 0

#include <avr/interrupt.h>
#include "MCP.h"

/**
 * @file
 * @brief Can driver NODE1
*/

/**
 * @brief Message struct to be sent by CAN
*/
typedef struct message {
    uint16_t ID;
    uint8_t data[8];
    uint8_t length;
} message_t;

volatile message_t node2_state_msg;
volatile message_t config_msg;
volatile message_t controls_msg;
volatile uint16_t score;

/**
 * @brief ID types for message struct
*/
typedef enum message_id {
	NODE2_STATE, CONFIG, CONTROLS, SCORE
} message_id_t;

/**
 * @brief button types for button data of CAN message with ID CONFIG
*/
typedef enum button {
    UNDEF, JOYSTICK, LEFT, RIGHT, BOTH
} button_t;

/**
 * @brief Initialize the Can bus
*/
void CAN_initialize();

/**
 * @brief Write message over the Can bus
   @param msg; Message to be sent.
*/
void CAN_write_message(message_t msg);

/**
 * @brief Receive message over the Can bus
*/
void CAN_receive_message();

#endif
