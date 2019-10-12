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
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "lib.h"
#include <avr/interrupt.h>


int main(void)
{
	UART_initialize();
    XMEM_initialize();
    OLED_initialize();

    SRAM_test();
    //volatile char *ext_ram = (char *) 0x1000; // Start address for the OLED
    //volatile char *ext_ram = (char *) 0x1400; // Start address for the ADC
    

    OLED_print_string("helo");
    OLED_goto_page(1);
    OLED_goto_column(0);
    OLED_print_string("i am");
    OLED_goto_page(2);
    OLED_goto_column(0);
    OLED_print_string("cool");
    OLED_invert_page(0);

    //OLED_home();
    //OLED_menu_interface();
	 
    //CAN_initilize();

    message_t msg;
    msg.ID = 1;
    msg.length = 3;
    msg.data[0] = 'K';
    msg.data[1] = 'U';
    msg.data[2] = 'K';

    
    while(1) {
        /*
        CAN_write_message(msg);
        if(MCP_read(MCP_CANINTF) & 0x01){
            message_t mg = CAN_receive_message();
            for(uint8_t f = 0;f<msg.length;f++){
                printf("msg2 = %d\n\r", mg.data[f]);
            }
            _delay_ms(10);
        }*/
    }
}

/*
ISR(INT0_vect){
    cli();
    printf("Interrupted");
    sei();
}*/