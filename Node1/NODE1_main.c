/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

//helo from armon
//ttyS0
#define F_CPU 16000000 // clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART_driver.h"
#include "XMEM_driver.h"
#include "ADC_driver.h"
#include "controller.h"
#include "OLED.h"
#include "OLED_interface.h"
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "lib.h"

int main(void)
{
	UART_initialize();
    XMEM_initialize();   
    OLED_initialize(); 
    //OLED_home();

    //OLED_menu_interface();
	
    CAN_initialize();
    
    printf("CANSTAT: %d\n\r", MCP_read(MCP_CANSTAT));
    message_t msg;
    msg.ID = 0;
    msg.length = 2;
    msg.data[0] = 'A';
    msg.data[1] = 'B';

    char B;
    message_t res;
    while(1) {
        _delay_ms(100);
        //printf("X=%d\tY=%d\n\r", controller_joystick_read_X(), controller_joystick_read_Y());
        CAN_write_message(msg);
        printf("Node 1 write: %c\n\r", msg.data[0]);
        //res = CAN_receive_message();
        //printf("Node 1 receive: %c\n\r", res.data[0]);
        //printf("helo");
        //controller_CAN_send();
        
    }
}

