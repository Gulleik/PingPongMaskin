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
//#include "OLED_interface.h"
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "lib.h"

int main(void)
{
	UART_initialize();
    CAN_initialize();
    XMEM_initialize();   
    //OLED_initialize();

    //OLED_interface();
    while(1) {
        controller_CAN_send();
        _delay_ms(100);
    }
}

