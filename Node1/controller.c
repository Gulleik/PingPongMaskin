#include "controller.h"
#include "CAN.h"
#include "ADC.h"
#include <avr/io.h>

void controller_initialize() {
    CAN_initialize();
    ADC_init();

    DDRB &= ~((1 << DDB1) | ~(1 << DDB2) | ~(1 << DDB3));
}

uint8_t controller_joystick_read_X(){
    char X = ADC_read(0b0101);
    controls_msg.data[0] = (uint8_t) X;
    return X;
}

uint8_t controller_joystick_read_Y(){
    char Y = ADC_read(0b0100);
    controls_msg.data[1] = (uint8_t) Y;
    return Y;
}

uint8_t controller_slider_read_L(){
    char S = ADC_read(0b0111);
    controls_msg.data[2] = (uint8_t) S;
    return S;
}

uint8_t controller_slider_read_R(){
    char S = ADC_read(0b0110);
    controls_msg.data[3] = (uint8_t) S;
    return S;
}

uint8_t controller_button_read(){
    uint8_t B = PINB & 0b00001110;

    enum BUTTON ret;

    if(B==0){
        ret =  JOYSTICK;
    }else if(B == 10){
        ret =  LEFT;
    }else if(B == 12){
        ret =  RIGHT;
    }else if(B == 14){
        ret =  BOTH;
    }else{
        ret = UNDEF;
    }
    printf("Raw B: %d,B: %d\n\r", B, ret);
    controls_msg.data[4] = (uint8_t) ret;
}

void controller_CAN_send() {
    controls_msg.length = 5;
    controls_msg.ID = CONTROLS;
    controller_joystick_read_X();
    controller_joystick_read_Y();
    controller_slider_read_L();
    controller_slider_read_R();
    controller_button_read();
    CAN_write_message(controls_msg);
    printf("X: %d, Y: %d, SL: %d, SR: %d, B: %d\n\r", 
                    controls_msg.data[0],
                    controls_msg.data[1],
                    controls_msg.data[2],
                    controls_msg.data[3],
                    controls_msg.data[4]
                );
}