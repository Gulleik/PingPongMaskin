#include "controller.h"
#include <avr/io.h>

char controller_joystick_read_X(){
     char X = ADC_read(0b0101);
    if(X > -1){
        X = X * 100/125-100;
    }else{
        X = (X +125)*100/125;
    }
    return X;
}

char controller_joystick_read_Y(){
    char Y = ADC_read(0b0100);
    if(Y > -1){
        Y =Y*100/125-100;
    }else{
        Y = (Y +125)*100/125;
    }
    return Y;
}

char controller_slider_read_L(){
    char S = ADC_read(0b0111);
    if(S < -1){
        S =S*50/125+100;
    }else{
        S = S*50/125;
    }
    return S;
}

char controller_slider_read_R(){
    char S = ADC_read(0b0110);
    if(S < -1){
        S =S*50/125+100;
    }else{
        S = S*50/125;
    }
    return S;
}

char controller_button_read(){
    DDRB = 0;
    char B = PINB;
    if(B==8){
        return 'r';
    }else if(B==4){
        return 'l';
    }else if(B==12){
        return 'b';
    }else{
        return 0;
    }
}

