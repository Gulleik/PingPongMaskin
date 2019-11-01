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
#include "IR_driver.h"
#include "Motor_driver.h"
#include "solenoid.h"

int main(void)
{
    
	UART_initialize(); 
    CAN_initialize();
    servo_driver_pwm_init();
    IR_internal_ADC_init();
    motor_driver_initialise();
    solenoid_init();

    while(1) {
        motor_driver_update_slider_ref(latest_message.data[3]);
        //printf("curr_pos: %d\tencoder: %d\n\r", curr_pos, motor_driver_encoder_read_byte());
        motor_driver_update_pos();
        servo_driver_pwm_controller(latest_message.data[0]);
        IR_internal_ADC_read();
        if(latest_message.data[4] != 0){
            solenoid_shoot();
        }
    }

    
    return 0;
}
