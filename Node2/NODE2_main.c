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
#include "UART.h"

#include "CAN_driver.h"
#include "MCP.h"
#include "lib.h"
#include "Servo.h"
#include "IR_driver.h"
#include "Motor.h"
#include "solenoid.h"

int main(void)
{
    
	UART_initialize(); 
    CAN_initialize();
    Servo_initialize();
    IR_internal_ADC_init();
    Motor_initialise();
    solenoid_init();

    while(1) {
        Motor_update_slider_ref(latest_message.data[3]);
        
        //printf("curr_pos: %d\tencoder: %d\n\r", curr_pos, motor_driver_encoder_read_byte());
        Motor_position_controller();
        Servo_set_position(latest_message.data[0]);
        IR_internal_ADC_read();
        if(latest_message.data[4] != 0){
            solenoid_shoot();
        }
    }

    
    return 0;
}