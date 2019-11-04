#ifndef CAN_H
#define CAN_H

#endif

#include <stdint.h>

enum message_IDs {
	INTERRUPT, CONTROLS = 5
};

struct message_t {
    uint16_t ID;
    uint8_t data[8];
    uint8_t length;
} typedef message_t;

volatile message_t latest_msg;
volatile message_t controls_msg;

void CAN_initialize();

void CAN_write_message(message_t msg);

message_t CAN_receive_message();
