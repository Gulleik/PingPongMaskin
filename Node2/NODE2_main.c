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
#include "Servo.h"
#include "IR.h"
#include "Motor.h"
#include "solenoid.h"
#include "timer.h"

void NODE2_initialize() {
	UART_initialize();
    printf("\n\rNode 2 initializing...\n\r");

    /*Initialize modules*/
    printf("\tUART\t\tOK\r\n");
    printf("\tCAN");
    printf("\t\tOK\r\n");
    printf("\tServo");
    Servo_initialize();
    printf("\t\tOK\r\n");
    printf("\tIR");
    IR_internal_ADC_initialize();
    printf("\t\tOK\r\n");
    printf("\tMotor");
    Motor_initialize();
    printf("\t\tOK\r\n");
    printf("\tSolenoid");
    solenoid_initialize();
    printf("\tOK\r\n");
    printf("\tTimer");
    timer_initialize();
    printf("\t\tOK\r\n");

    printf("Initialization complete\n\r");
}

int main(void)
{
    NODE2_initialize();

    uint8_t prev_state = -1;
    
    /*Initiate node 2 to idle state and default configuration*/
	node2_state_msg.ID = NODE2_STATE;
    score_msg.ID = SCORE;
    score_msg.data[0] = 1;
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
            case STATE_IDLE:
                if (prev_state != STATE_IDLE) {
                    prev_state = STATE_IDLE;
                    timer_disable(IR_ADC_TIMER);
                    timer_disable(CONTROLLER_TIMER);
                }
                break;

            case STATE_PLAY:
                if (prev_state != STATE_PLAY) {
                    prev_state = STATE_PLAY;
                    timer_enable(IR_ADC_TIMER);
                    timer_enable(CONTROLLER_TIMER);
                    Motor_calibrate();
                }
                if( timer_interrupt == 1){
                    Motor_position_controller();
                    Servo_set_position(controls_msg.data[0]);
                    timer_interrupt = 0;
                }
                else if(controls_msg.data[4] == RIGHT){
                    solenoid_shoot();
                }
                _delay_ms(50);
                break;
        }
    }

    
    return 0;
}