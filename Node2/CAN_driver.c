#include "CAN_driver.h"
#include "MCP_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void CAN_initialize(){
    MCP_driver_reset();

    /*Setup for external interrupt operation*/
    sei();  //Enable global interrupts
    EIMSK |= (1 << INT0);    //Set INT0 pin as external interrupt-pin
    EICRA |= (1 << ISC01);  //Interrupt trigger on rising edge
    EIFR |= (1 << INTF0);   //Clear interrupt flag on INT0
    MCP_bit_modify(MCP_CANINTE, 0x1, 0xFF); //Enable Interrupts on CAN reception
    MCP_bit_modify(MCP_CANINTF, 0x1, 0x00); //Clear interrupt flag on CAN reception
    
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
    //mcp_modify_bit(MCP_CANINTE, 1<<2); // 1<<2 = TX0IE
    
    //Initiate transmission on buffer 0
    MCP_write(MCP_TXB0CTRL, 1<<3); //1<<3 = TXREQ

    MCP_RTS(0x00); //RTS buffer 0
}

message_t CAN_receive_message(){
    message_t msg;
    //msg.ID = -1;

    if(MCP_read(MCP_CANINTF) & 0x01 ){
        MCP_bit_modify(MCP_CANINTF, 0x01, 0);
        msg.ID = (MCP_read(MCP_RXB0SIDH) << 3);
        msg.ID |= (MCP_read(MCP_RXB0SIDL) >> 5);

        msg.length = (MCP_read(MCP_RXB0DLC) & 0x0F);

        for(uint8_t i = 0;i < msg.length;i++){
            msg.data[i] = MCP_read(MCP_RXB0D0+i);
        }
    }

    //printf("Node 2 CAN receive: \n\r\t\t\t"); //sloyf det her seinre ellerno piss
    //for (int i = 0; i < msg.length; i++) {
    //    printf("%d ", msg.data[i]);
    //}
    //printf("\n\r");
    
    return msg;
}
