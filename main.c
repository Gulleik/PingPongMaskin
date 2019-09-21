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
    OLED_reset();
    OLED_goto_line(3);
    //OLED_write_c(0x0);
    int i = 0;
    while (1) {
        _delay_ms(100);
        OLED_write_char('A');
    }
    //OLED_goto_column(20);
    //OLED_reset();
    //OLED_print("vi klarer oss uten deg jj");
}