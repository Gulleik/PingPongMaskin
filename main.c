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

int main(void)
{
	UART_driver_initialize();
    SRAM_driver_initialize();
    //SRAM_driver_write(0x0000, 0x00);
    volatile char *ext_OLED = (char *) 0x1000;
    volatile char *ext_ADC = (char *) 0x1400;
    volatile char *ext_SRAM = (char *) 0x1800;
    SRAM_test();
    //ext_SRAM[0] = 0x55;
    //ext_ADC[0] = 0x00;
    //ext_OLED[0] = 0x00;
    
    while(1);
       /* ext[0] = 0x00;
        printf("0\n\r");
        _delay_ms(1000);
        ext[1] = 0x00;
        printf("1\n\r");
        _delay_ms(1000);
        ext[2] = 0x00;
        printf("2\n\r");
        _delay_ms(1000);
        ext[3] = 0x00;
        printf("3\n\r");
        _delay_ms(1000);
       */
    
}