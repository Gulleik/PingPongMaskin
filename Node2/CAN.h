#ifndef CAN_H
#define CAN_H

#endif

#include <stdint.h>

struct message_t {
    uint16_t ID;
    uint8_t data[8];
    uint8_t length;
} typedef message_t;

enum message_IDs {
	INTERRUPT, CONTROLS = 5
};

volatile message_t latest_msg;
volatile message_t controls_msg;

/**
 * initialize can driver
*/
void CAN_initialize();

/**
 * Write message over the Can bus
   @param msg; message to be sent.
*/
void CAN_write_message(message_t msg);

/**
 * Receive message over the Can bus
   @param msg; message to be sent.
*/
message_t CAN_receive_message();
