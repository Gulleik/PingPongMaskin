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

    servo_driver_pwm_init();

    message_t msg;
    uint8_t X;
    while(1) {
        _delay_ms(300);
        msg = CAN_receive_message();
        X = msg.data[0];
        printf("Node 2 receive: X = %d\n\r", X);
        servo_driver_pwm_controller(X);
    }
}

/*
ISR(INT0_vect){
    cli();
    printf("Interrupted");
    sei();
}*/