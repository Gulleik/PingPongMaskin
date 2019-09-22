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
    //OLED_reset_position();
    OLED_goto_column(0x00);
	OLED_goto_line(0x00);
	//OLED_print_char('K');
	OLED_print_string("Helo");
	
	/*
	char k = 0;
	while (1) {
		//OLED_write_c(0xa5);
		OLED_write_d(k++%0xFF);
		_delay_ms(10);
    }*/
}