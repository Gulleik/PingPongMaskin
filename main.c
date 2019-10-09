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
#include "SPI_communication_driver.h"
#include "MCP_driver.h"


int main(void)
{
	UART_initialize();
    XMEM_initialize();

    OLED_initialize();
    //OLED_home();
    
    //OLED_clear();
    //OLED_reset_position();
    //OLED_menu_interface();
	 
    SPI_master_initialize();
    MCP_driver_reset();
    MCP_write(MCP_CANCTRL, MODE_LOOPBACK);

    printf("MCP_CANCTRL: %d\n\r", MCP_read(MCP_CANCTRL));
    _delay_ms(100);
    MCP_bit_modify(MCP_CANCTRL, 0b10000000, 0b10000000);
    printf("Modified MCP_CANCTRL: %d\n\r", MCP_read(MCP_CANCTRL));

    while(1) {
    }
}