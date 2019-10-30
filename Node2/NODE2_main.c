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
#include "Motor_driver.h"
#include <avr/interrupt.h>

int main(void)
{
	UART_initialize(); 
    CAN_initialize();
    servo_driver_pwm_init();
    IR_internal_ADC_init();
    motor_driver_initialise();
    message_t msg;

    while(1) {
        //if (UART_receive() == 'e') {
        //    printf("latest received message: %c\n\r", latest_message.data[0]);
        //}
        msg = latest_message;
        IR_internal_ADC_read();
        
        printf("X: %d, Y: %d, SL: %d, SR: %d, B: %d\n\r", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4]);

        printf("Speed: %d\n\r", motor_driver_calculate_speed(msg.data[0]));
        //motor_driver_run(msg.data[0]);


        _delay_ms(200);
    }
}
