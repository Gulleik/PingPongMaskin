#include "Motor.h"

#define F_CPU 16000000 // clock frequency in Hz

#include <util/delay.h>

uint16_t MAX_pos;
uint16_t MIN_pos;
int16_t i_error = 0;
int16_t d_error = 0;
int16_t previos_error = 0;
uint16_t K_p;   //DEFAULT 80
uint16_t K_i;   //DEFAULT 10
uint16_t K_d;   //DEFAULT 100

// Max speed a value between 0 and 255
uint8_t Max_speed; //DEFAULT 120

void Motor_reset_encoder(){
    PORTH &= ~(1 << RST); //resetting encoder pos
    _delay_us(30);
    PORTH |= (1 << RST); // --||--
}

void Motor_set_dir(uint8_t dir){
    if (dir == 0){
        PORTH |= (1 << DIR); // høgre
    }else{
        PORTH &= ~(1 << DIR); // venstre
    }
}

uint16_t Motor_encoder_read_data(){
    /*Enable encoder*/
    PORTH &= ~(1 << OE);
    uint16_t data;

    /*Read high Byte of signal*/
    PORTH &= ~(1 << SEL); //Set SEL low to get high byte
    _delay_us(30);
    data = (PINK << 0x8);

    /*Read low Byte of signal*/
    PORTH |= (1 << SEL); //Set SEL high to get low byte
    _delay_us(30);
    data |= PINK;
    /*Disable encoder*/
    PORTH |= (1 << OE);
    return data;
}

void Motor_adjust_speed(uint8_t speed){
    unsigned char msg[3];
    msg[0] = 0b01010000;
    msg[1] = 0;
    if (speed > Max_speed){
        speed = Max_speed;
    }
    msg[2] = speed;
    TWI_Start_Transceiver_With_Data(msg,3);
}

void Motor_initialize(){
    TWI_Master_Initialize();
    position_ref = 0;
    DDRH = 0xFF;
    DDRK = 0x00;
    Motor_enable_motor(ON);
}

void Motor_calibrate(uint8_t max_speed_conf, uint8_t K_p_conf, uint8_t K_i_conf, uint8_t K_d_conf) {
    Motor_set_dir(MOTOR_RIGHT);
	Motor_adjust_speed(80);
	_delay_ms(1000);

    /*Log right encoder position*/
	Motor_adjust_speed(0);
    _delay_ms(100);
	Motor_reset_encoder();
	MIN_pos = Motor_encoder_read_data();
	
	Motor_set_dir(MOTOR_LEFT);
	Motor_adjust_speed(80);
	_delay_ms(1000);

    /*Log left encoder position*/
	Motor_adjust_speed(0);
    _delay_ms(100);
	MAX_pos = Motor_encoder_read_data();

	/*Get config data from node 1*/
    K_p = K_p_conf; //1 = Data pos for K_p
    K_i = K_i_conf; //2 = Data pos for K_i
    K_d = K_d_conf; //3 = Data pos for K_d
    Max_speed = max_speed_conf;
}

void Motor_enable_motor(uint8_t state){
    if (state){
        PORTH |= (1 << EN);
    }else{
        PORTH &= ~(1 << EN);
    }
}

void Motor_update_slider_ref(uint8_t slider_pos){
    float scale = (float)(MAX_pos-MIN_pos)/255;
    position_ref = MAX_pos - scale*((uint16_t) slider_pos);
}

void Motor_position_controller(uint8_t reference){
    /*Update reference in accordance with slider position*/
    Motor_update_slider_ref(reference);
    int16_t e = (position_ref - Motor_encoder_read_data());
    e = e/100;
    i_error += e;
    d_error = -e + previos_error;
    int16_t u = e*K_p + i_error*K_i - K_d*d_error;
    if( u < 0 ){
        Motor_set_dir(MOTOR_RIGHT);
    }else{
        Motor_set_dir(MOTOR_LEFT);
    }
    u = u/50;
    u = abs(u);
    if (u > Max_speed){
        u = Max_speed;
    }
    Motor_adjust_speed(u);
    previos_error = e;
}