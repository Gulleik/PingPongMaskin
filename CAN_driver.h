#ifndef CAN_H
#define CAN_H

#endif

#include <stdint.h>

struct message_t {
    uint16_t ID;
    uint8_t data[8];
    uint8_t length;
} typedef message_t;


void CAN_initilize();

void CAN_write_message(message_t msg);

message_t CAN_receive_message();
