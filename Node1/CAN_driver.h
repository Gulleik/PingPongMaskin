#ifndef CAN_H
#define CAN_H

#define CONF_DEFAULT_TOP_SPEED 120
#define CONF_DEFAULT_Kp 80
#define CONF_DEFAULT_Ki 10
#define CONF_DEFAULT_Kd 100

#endif

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

void CAN_initialize();

void CAN_write_message(message_t msg);

void CAN_receive_message();
