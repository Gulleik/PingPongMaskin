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



#include <stdint.h>

struct message_t {
    uint16_t ID;
    uint8_t data[8];
    uint8_t length;
} typedef message_t;

enum MESSAGE_ID {
	NODE2_STATE, CONFIG, CONTROLS
};

enum BUTTON {
    UNDEF, JOYSTICK, LEFT, RIGHT, BOTH
};

volatile message_t node2_state_msg;
volatile message_t config_msg;
volatile message_t controls_msg;

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
