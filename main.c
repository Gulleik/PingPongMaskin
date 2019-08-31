/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

#define F_CPU 16000000 // clock frequency in Hz
#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"
#include "SRAM_driver.h"

int main(void)
{
	UART_driver_initialize();
    SRAM_driver_initialize();
    //SRAM_driver_write(0x0000, 0x00);
    uint16_t *ext = (char*) 0xFFFF;
    while(1){
        ext[0] = 0xFF;
    }
}