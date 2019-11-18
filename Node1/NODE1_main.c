/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

//helo from armon
//ttyS0
#define F_CPU 4915200 // clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "UART.h"
#include "ADC.h"
#include "controller.h"
#include "OLED.h"
#include "OLED_interface.h"
#include "CAN.h"
#include "MCP.h"
#include "MCP_registers.h"
#include "timer.h"

void XMEM_initialize(){
    //Enabling External Memory Interface
    MCUCR |= (1<<SRE);
    
    //masking first four bits
    SFIOR |= (1<<XMM2);
}


int main(void)
{
    UART_initialize();
    XMEM_initialize();
    OLED_initialize(60); //60Hz refresh rate
    CAN_initialize();
    timer_game_enable();
    
    OLED_interface();

    while(1) {
        //OLED_clear();   
        /*controller_CAN_send();
        printf("X: %d, Y: %d, SL: %d, SR: %d, B: %d\n\r", 
                    controls_msg.data[0],
                    controls_msg.data[1],
                    controls_msg.data[2],
                    controls_msg.data[3],
                    controls_msg.data[4]
                );*/
                _delay_ms(100);
    }
}

