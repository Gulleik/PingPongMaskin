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

#include "CAN.h"
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

    uint8_t Motor_calibrated;
    /*Initiate node 2 to idle state and default configuration*/
	node2_state_msg.ID = NODE2_STATE;
	config_msg.ID = CONFIG;

    while(1) {
        printf("STATE: %d CONFIGS: speed = %d, Kp = %d, Ki = %d, Kd = %d, Inv_ser = %d, Inv_mot = %d\n\r",
            node2_state_msg.data[0],
            config_msg.data[0],
            config_msg.data[1],
            config_msg.data[2],
            config_msg.data[3],
            config_msg.data[4],
            config_msg.data[5]
        );
        switch (node2_state_msg.data[0]) {
            case 0: //IDLE STATE
                Motor_calibrated = 0;
                break;
            case 1: //PLAY STATE
                if (!Motor_calibrated) {
                    Motor_calibrate();
                    Motor_calibrated = 1;
                }

                Motor_update_slider_ref(controls_msg.data[3]);
                Motor_position_controller();
                Servo_set_position(controls_msg.data[0]);
                //IR_internal_ADC_read();
                /*printf("X: %d, Y: %d, SL: %d, SR: %d, B: %d\n\r", 
                    controls_msg.data[0],
                    controls_msg.data[1],
                    controls_msg.data[2],
                    controls_msg.data[3],
                    controls_msg.data[4]
                );*/
                if(controls_msg.data[4] == RIGHT){
                    solenoid_shoot();
                }
                _delay_ms(50);
                break;
        }
    }

    
    return 0;
}