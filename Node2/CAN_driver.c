#include "CAN_driver.h"
#include "MCP_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void CAN_initialize(){
    /*Reset MCP*/
    MCP_reset();

    /*Setup for external interrupt operation*/
    cli();
    EIMSK |= (1 << INT2);    //Set INT2 pin as external interrupt-pin
    EICRB |= (0b10 << ISC20);  //Interrupt trigger on INT2 on falling edge
    EIFR |= (1 << INTF2);   //Clear interrupt flag on INT2
    MCP_bit_modify(MCP_CANINTF, 0x1, 0x00); //Clear interrupt flag on CAN reception
    MCP_bit_modify(MCP_CANINTE, 0x1, 0xFF); //Enable Interrupts on CAN reception
    sei();  //Enable global interrupts
    
    /*Set MCP to normal mode*/
    MCP_bit_modify(MCP_CANCTRL, (0b111<<5), MODE_NORMAL);
}

void CAN_write_message(message_t msg) {

    MCP_write(MCP_TXB0SIDH, (uint8_t) msg.ID>>3);
    MCP_write(MCP_TXB0SIDL, (uint8_t) msg.ID<<5);

    MCP_write(MCP_TXB0DLC, msg.length);

    for (int i = 0; i < msg.length; i++) {
        MCP_write((uint8_t) (MCP_TXB0D0 + i), msg.data[i]);
    }
    
    //Initiate transmission on buffer 0
    MCP_write(MCP_TXB0CTRL, 1<<3); //1<<3 = TXREQ

    MCP_Request_To_Send(0x00); //RTS buffer 0
}

message_t CAN_receive_message(){
    /*Update latest_message with new received data*/
    latest_message.ID = (MCP_read(MCP_RXB0SIDH) << 3);
    latest_message.ID |= (MCP_read(MCP_RXB0SIDL) >> 5);
    latest_message.length = (MCP_read(MCP_RXB0DLC) & 0x0F);

    for(uint8_t i = 0;i < latest_message.length;i++){
        latest_message.data[i] = MCP_read(MCP_RXB0D0+i);
    }

    /*Clear interrupt flag on CAN reception*/
    MCP_bit_modify(MCP_CANINTF, 0x01, 0);
    return latest_message;
}

ISR(INT2_vect){
    cli();
    CAN_receive_message();
    sei();
}

ISR(BADISR_vect){
}