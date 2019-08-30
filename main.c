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
	UART_driver_initialize();

    UART_driver_transmit('A');
}