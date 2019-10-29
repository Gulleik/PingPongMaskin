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
    IR_internal_ADC_init();

    message_t msg;
    msg.length = 1;
    msg.ID = 0;
    msg.data[0] = 'a';
    uint8_t var;
    while(1) {
        _delay_ms(300);
        msg = CAN_receive_message();
        //var = IR_internal_ADC_read();
        //printf("ADC result: %x\n\r", var);
        printf("NODE2 receive: %c\n\r", msg.data[0]);
        //if (UART_receive() == 'e') {
        //    CAN_write_message(msg);
        //    printf("Node 2 write: %c\n\r", msg.data[0]);
        //}
    }
}
