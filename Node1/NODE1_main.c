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
    printf("\tUART\t\tOK\r\n");
    printf("\tCAN");
    CAN_initialize();
    printf("\t\tOK\r\n");
    printf("\tXMEM");
    XMEM_initialize(); 
    printf("\t\tOK\r\n");
    printf("\tOLED");
    OLED_initialize();
    printf("\t\tOK\r\n");

    printf("Completed with no errors\n\r");
}

int main(void)
{
    NODE1_initialize();

    OLED_interface();
    while(1);
}

