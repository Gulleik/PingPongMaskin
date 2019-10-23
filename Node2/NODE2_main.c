/* Test.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : gulle
 */ 

//helo from armon
//ttyACM0
#define F_CPU 16000000 // clock frequency in Hz

#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "lib.h"
#include "servo_driver.h"
#include <avr/interrupt.h>

int main(void)
{
	UART_initialize(); 

    //OLED_home();
	 
    CAN_initialize();

    printf("CANSTAT: %d\n\r", MCP_read(MCP_CANSTAT));

    servo_driver_pwm_init();
    uint8_t X_pos;
    message_t msg;
    while(1) {
        _delay_ms(300);
        msg = CAN_receive_message();
        printf("Node 2 receive: \n\r", msg.data[0]);
        //servo_driver_pwm_controller(X_pos);
    }
}

/*
ISR(INT0_vect){
    cli();
    printf("Interrupted");
    sei();
}*/