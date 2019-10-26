#include "controller.h"
#include "CAN_driver.h"
#include <avr/io.h>

uint8_t controller_joystick_read_X(){
    char X = ADC_read(0b0101);
    return X;
}

uint8_t controller_joystick_read_Y(){
    char Y = ADC_read(0b0100);
    return Y;
}

uint8_t controller_slider_read_L(){
    char S = ADC_read(0b0111);
    return S;
}

uint8_t controller_slider_read_R(){
    char S = ADC_read(0b0110);
    return S;
}

char controller_button_read(){
    DDRB &= ~(1 << DDB1) & ~(1 << DDB2) & ~(1 << DDB3);
    
    char B = PINB;
    if(B==48){
        return 'j';
    }else if(B > 58 && B <= 59){
        return 'r';
    }else if(B > 60 && B <= 61){
        return 'l';
    }else if(B > 62 && B <= 64){
        return 'b';
    }else{
        return 0;
    }
}


void controller_CAN_send() {
    message_t msg;
    msg.length = 5;
    msg.ID = 0;
    msg.data[0] = controller_joystick_read_X();
    msg.data[1] = controller_joystick_read_Y();
    msg.data[2] = controller_slider_read_L();
    msg.data[3] = controller_slider_read_R();
    msg.data[4] = controller_button_read();
    CAN_write_message(msg);
}