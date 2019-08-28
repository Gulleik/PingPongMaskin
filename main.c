/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

#define F_CPU 16000000 // clock frequency in Hz
#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"

int main(void)
{
	DDRD = 0x01;
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 1;
		_delay_ms(5);
		PORTD = 0;
		_delay_ms(5);
    }
}