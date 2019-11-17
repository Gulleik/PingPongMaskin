/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

//helo from armon
//ttyS0
#define F_CPU 4915200 // clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "XMEM.h"
#include "ADC.h"
#include "controller.h"
#include "OLED.h"
#include "OLED_interface.h"
#include "CAN.h"
#include "MCP.h"
#include "MCP_registers.h"
#include "lib.h"

void NODE1_initialize() {
	UART_initialize();
    
    printf("Node 1 initializing...\n\r");

    /*Initialize modules*/
    //printf("\tUART\t\tOK\r\n");
    //printf("\tCAN");
    CAN_initialize();
    //printf("\t\tOK\r\n");
    //printf("\tXMEM");
    XMEM_initialize(); 
    //printf("\t\tOK\r\n");
    //printf("\tOLED");
    OLED_initialize();
    //printf("\t\tOK\r\n");

    printf("Initialization complete\n\r");
}

int main(void)
{
    NODE1_initialize();

    SRAM_test();
    OLED_interface();
    while(1) {
        /*printf("X: %d, Y: %d, SL: %d, SR: %d, B: %d\n\r", 
                    controls_msg.data[0],
                    controls_msg.data[1],
                    controls_msg.data[2],
                    controls_msg.data[3],
                    controls_msg.data[4]
                );*/
    }
}

