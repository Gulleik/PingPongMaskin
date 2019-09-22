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


int main(void)
{
	UART_initialize();
    XMEM_initialize();

    OLED_initialize();
    OLED_clear();
    OLED_reset_position();
	
	int x = 0;
	int y = 0;
	OLED_get_main_menu();
	while (1) {
		
    }
}