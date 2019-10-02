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

    
    //OLED_initialize();
    //OLED_home();
    
    //OLED_clear();
    //OLED_reset_position();
    //OLED_menu_interface();
	
    
    SPI_master_initialize();
    MCP_driver_reset();
    MCP_write(0x00, 0x55);
    printf("%d", MCP_read(0x00));
    while(1) {
        //SPI_write_byte(0x81);
        //MCP_RTS();
        //MCP_write(0x00, 0x55);
        //printf("%d", MCP_read(0x00));
    }
}