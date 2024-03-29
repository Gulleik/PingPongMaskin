#include "CAN.h"

void CAN_initialize(){
    /*Initialize MCP*/
    MCP_initialize();

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

void CAN_receive_message(){
    message_t msg;
    /*Update msg with new received data*/
    msg.ID = (MCP_read(MCP_RXB0SIDH) << 3);
    msg.ID |= (MCP_read(MCP_RXB0SIDL) >> 5);
    msg.length = (MCP_read(MCP_RXB0DLC) & 0x0F);

    for(uint8_t i = 0;i < msg.length;i++){
        msg.data[i] = MCP_read(MCP_RXB0D0+i);
    }

    /*Save to corresponding message types*/
    switch(msg.ID) {
        case NODE2_STATE:
            node2_state_msg.ID = msg.ID;
            node2_state_msg.length = msg.length;
            for (uint8_t i = 0; i < msg.length; i++) {
                node2_state_msg.data[i] = msg.data[i];
            }
            break;
        case CONFIG:
            config_msg.ID = msg.ID;
            config_msg.length = msg.length;
            for (uint8_t i = 0; i < msg.length; i++) {
                config_msg.data[i] = msg.data[i];
            }
            break;
        case CONTROLS:
            controls_msg.ID = msg.ID;
            controls_msg.length = msg.length;
            for (uint8_t i = 0; i < msg.length; i++) {
                controls_msg.data[i] = msg.data[i];
            }
            break;
        default:
            break;
    }

    /*Clear interrupt flag on CAN reception*/
    MCP_bit_modify(MCP_CANINTF, 0x01, 0);
}

ISR(INT2_vect){
    cli();
    CAN_receive_message();
    sei();
}

ISR(BADISR_vect){
}