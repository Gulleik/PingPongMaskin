/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

#define F_CPU 16000000 // clock frequency in Hz
#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"
#include "XMEM_driver.h"
#include "ADC_driver.h"
#include "controller.h"

int main(void)
{
    char * Ch1 = 0b0100;
    char * Ch2 = 0b0101;
    char * Ch3 = 0b0110;
    char * Ch4 = 0b0111;
	UART_initialize();
    XMEM_initialize();
    while(1) {
        char Y = controller_button_read();
        printf("Y=%d\n\r", Y);
        _delay_ms(100);
    }  
}