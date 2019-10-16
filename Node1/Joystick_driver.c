#include "Joystic_controller.h"
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