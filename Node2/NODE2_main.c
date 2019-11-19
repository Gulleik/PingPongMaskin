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
#include "IR.h"
#include "timer.h"
#include "Motor.h"
#include "Servo.h"
#include "solenoid.h"

void NODE2_initialize() {
	UART_initialize();
    Servo_initialize();
    IR_internal_ADC_initialize();
    Motor_initialize();
    solenoid_initialize();
    timer_initialize();
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
        printf("X: %d, Y: %d, SL: %d, SR: %d, B: %d\n\r",
                controls_msg.data[0],
                controls_msg.data[1],
                controls_msg.data[2],
                controls_msg.data[3],
                controls_msg.data[4]
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
                    Motor_calibrate(config_msg.data[0],     //Top speed
                                    config_msg.data[1],     //K_p
                                    config_msg.data[2],     //K_i
                                    config_msg.data[3]);    //K_d
                }
                if(IR_interrupt == 1){
                    IR_internal_ADC_read();
                    IR_interrupt == 0;
                }
                if(controller_interrupt == 1){
                    Motor_position_controller(config_msg.data[5] ? controls_msg.data[2] : controls_msg.data[3]);
                    Servo_set_position(controls_msg.data[0], config_msg.data[4]);
                    controller_interrupt = 0;
                }
                if(controls_msg.data[4] == RIGHT){
                    solenoid_shoot();
                }
                break;
        }
    }
    return 0;
}