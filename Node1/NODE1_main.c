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

int main(void)
{
    controller_initialize();
	UART_initialize();
    CAN_initialize();
    XMEM_initialize();   
    OLED_initialize();

    OLED_interface();
    while(1){
        printf("main loop\n\r");
    }
}

