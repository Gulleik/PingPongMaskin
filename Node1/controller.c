#include "controller.h"

void controller_initialize() {
    CAN_initialize();

    /*Set pin 1, 2 and 3 on port B as input*/
    DDRB &= ~((1 << DDB1) | ~(1 << DDB2) | ~(1 << DDB3));
}

void controller_joystick_read_X(){
    /*Read ADC on address corresponding to joystick X-axis*/
    char X = ADC_read((uint8_t*) 0b0101);

    /*Save digital value of joystick X-axis to controls message*/
    controls_msg.data[0] = (uint8_t) X;
}

void controller_joystick_read_Y(){
    /*Read ADC on address corresponding to joystick Y-axis*/
    char Y = ADC_read((uint8_t*) 0b0100);

    /*Save digital value of joystick Y-axis to controls message*/
    controls_msg.data[1] = (uint8_t) Y;
}

void controller_slider_read_L(){
    /*Read ADC on address corresponding to left slider*/
    char S = ADC_read((uint8_t*) 0b0111);

    /*Save digital value of left slider to controls message*/
    controls_msg.data[2] = (uint8_t) S;
}

void controller_slider_read_R(){
    /*Read ADC on address corresponding to right slider*/
    char S = ADC_read((uint8_t*) 0b0110);

    /*Save digital value of right slider to controls message*/
    controls_msg.data[3] = (uint8_t) S;
}

void controller_button_read(){
    /*Read analog button value to digital 8 bit variable*/
    uint8_t B = PINB & 0b00001110;

    /*Declare button type variable*/
    button_t ret;
    if(B==0){
        ret = JOYSTICK;
    }else if(B == 10){
        ret = LEFT;
    }else if(B == 12){
        ret = RIGHT;
    }else if(B == 14){
        ret = BOTH;
    }else{
        ret = UNDEF;
    }

    /*Save button type to controls message*/
    controls_msg.data[4] = (uint8_t) ret;
}

void controller_CAN_send() {
    /*Read all control values*/
    controls_msg.length = 5;
    controls_msg.ID = CONTROLS;
    controller_joystick_read_X();
    controller_joystick_read_Y();
    controller_slider_read_L();
    controller_slider_read_R();
    controller_button_read();

    /*Send all control values*/
    CAN_write_message(controls_msg);
}