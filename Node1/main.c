/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

//helo from armon
#define F_CPU 16000000 // clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"
#include "XMEM_driver.h"
#include "ADC_driver.h"
#include "controller.h"
#include "OLED.h"
#include "OLED_interface.h"
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "lib.h"
#include <avr/interrupt.h>

int main(void)
{
	UART_initialize();
    XMEM_initialize();   
    OLED_initialize(); 
    //OLED_home();

    //OLED_menu_interface();
	 
    CAN_initialize();

    message_t msg;
    msg.ID = 1;
    msg.length = 3;
    msg.data[0] = 'K';
    msg.data[1] = 'U';
    msg.data[2] = 'K';

    printf("CANSTAT: %d\n\r", MCP_read(MCP_CANSTAT));
    
    while(1) {
        CAN_write_message(msg);
        char mg = UART_receive();
        printf("message test; %d\n\r", mg);
    }
}

/*
ISR(INT0_vect){
    cli();
    printf("Interrupted");
    sei();
}*/