
#include "OLED.h"
#include "lib.h"
#include "fonts.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "controller.h"

const unsigned char PROGMEM font[95][5] = {
	{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, //
	{0b00000000,0b00000000,0b01011110,0b00000000,0b00000000}, // !
	{0b00000000,0b00001110,0b00000000,0b00001110,0b00000000}, // "
	{0b00101000,0b01111100,0b00101000,0b01111100,0b00101000}, // #
	{0b00001000,0b01010100,0b01111100,0b01010100,0b00100000}, // $
	{0b00100110,0b00010000,0b00001000,0b01100100,0b00000000}, // %
	{0b00101000,0b01010100,0b00101000,0b01000000,0b00000000}, // &
	{0b00000000,0b00000000,0b00001110,0b00000000,0b00000000}, // '
	{0b00000000,0b00111100,0b01000010,0b00000000,0b00000000}, // (
	{0b00000000,0b01000010,0b00111100,0b00000000,0b00000000}, // )
	{0b00000000,0b01010100,0b00111000,0b01010100,0b00000000}, // *
	{0b00010000,0b00010000,0b01111100,0b00010000,0b00010000}, // +
	{0b00000000,0b10000000,0b01100000,0b00100000,0b00000000}, // ,
	{0b00010000,0b00010000,0b00010000,0b00010000,0b00000000}, // -
	{0b00000000,0b01100000,0b01100000,0b00000000,0b00000000}, // .
	{0b00100000,0b00010000,0b00001000,0b00000100,0b00000000}, // /
	{0b00000000,0b00111100,0b01000010,0b00111100,0b00000000}, // 0
	{0b00000000,0b01000100,0b01111110,0b01000000,0b00000000}, // 1
	{0b01000100,0b01100010,0b01010010,0b01001100,0b00000000}, // 2
	{0b00100010,0b01001010,0b01001010,0b00110110,0b00000000}, // 3
	{0b00011000,0b00010100,0b01111110,0b00010000,0b00000000}, // 4
	{0b00101110,0b01001010,0b01001010,0b00110010,0b00000000}, // 5
	{0b00111100,0b01001010,0b01001010,0b00110000,0b00000000}, // 6
	{0b00000010,0b01100010,0b00011010,0b00000110,0b00000000}, // 7
	{0b00110100,0b01001010,0b01001010,0b00110100,0b00000000}, // 8
	{0b00001100,0b01010010,0b01010010,0b00111100,0b00000000}, // 9
	{0b00000000,0b01101100,0b01101100,0b00000000,0b00000000}, // :
	{0b10000000,0b01101100,0b00101100,0b00000000,0b00000000}, // ;
	{0b00000000,0b00010000,0b00101000,0b01000100,0b00000000}, // <
	{0b00101000,0b00101000,0b00101000,0b00101000,0b00000000}, // =
	{0b00000000,0b01000100,0b00101000,0b00010000,0b00000000}, // >
	{0b00000000,0b00000100,0b01010010,0b00001100,0b00000000}, // ?
	{0b00111100,0b01000010,0b01011010,0b00011100,0b00000000}, // @
	{0b01111100,0b00010010,0b00010010,0b01111100,0b00000000}, // A
	{0b01111110,0b01001010,0b01001010,0b00110100,0b00000000}, // B
	{0b00111100,0b01000010,0b01000010,0b00100100,0b00000000}, // C
	{0b01111110,0b01000010,0b01000010,0b00111100,0b00000000}, // D
	{0b01111110,0b01001010,0b01001010,0b01000010,0b00000000}, // E
	{0b01111110,0b00001010,0b00001010,0b00000010,0b00000000}, // F
	{0b00111100,0b01000010,0b01010010,0b01110100,0b00000000}, // G
	{0b01111110,0b00001000,0b00001000,0b01111110,0b00000000}, // H
	{0b00000000,0b01000010,0b01111110,0b01000010,0b00000000}, // I
	{0b00100000,0b01000000,0b01000000,0b00111110,0b00000000}, // J
	{0b01111110,0b00011000,0b00100100,0b01000010,0b00000000}, // K
	{0b01111110,0b01000000,0b01000000,0b01000000,0b00000000}, // L
	{0b01111110,0b00001100,0b00001100,0b01111110,0b00000000}, // M
	{0b01111110,0b00001100,0b00110000,0b01111110,0b00000000}, // N
	{0b00111100,0b01000010,0b01000010,0b00111100,0b00000000}, // O
	{0b01111110,0b00010010,0b00010010,0b00001100,0b00000000}, // P
	{0b00111100,0b01100010,0b01000010,0b10111100,0b00000000}, // Q
	{0b01111110,0b00010010,0b00110010,0b01001100,0b00000000}, // R
	{0b00100100,0b01001010,0b01010010,0b00100100,0b00000000}, // S
	{0b00000000,0b00000010,0b01111110,0b00000010,0b00000000}, // T
	{0b00111110,0b01000000,0b01000000,0b00111110,0b00000000}, // U
	{0b00011110,0b01100000,0b01100000,0b00011110,0b00000000}, // V
	{0b01111110,0b00110000,0b00110000,0b01111110,0b00000000}, // W
	{0b01100110,0b00011000,0b00011000,0b01100110,0b00000000}, // X
	{0b00000000,0b00001110,0b01110000,0b00001110,0b00000000}, // Y
	{0b01100010,0b01010010,0b01001010,0b01000110,0b00000000}, // Z
	{0b00000000,0b01111110,0b01000010,0b01000010,0b00000000}, // [
	{0b00000100,0b00001000,0b00010000,0b00100000,0b00000000}, // "\"
	{0b00000000,0b01000010,0b01000010,0b01111110,0b00000000}, // ]
	{0b00000000,0b00000100,0b00000010,0b00000100,0b00000000}, // ^
	{0b01000000,0b01000000,0b01000000,0b01000000,0b00000000}, // _
	{0b00000000,0b00000010,0b00000100,0b00000000,0b00000000}, // `
	{0b00110000,0b01001000,0b00101000,0b01111000,0b00000000}, // a
	{0b01111110,0b01001000,0b01001000,0b00110000,0b00000000}, // b
	{0b00110000,0b01001000,0b01001000,0b00000000,0b00000000}, // c
	{0b00110000,0b01001000,0b01001000,0b01111110,0b00000000}, // d
	{0b00110000,0b01101000,0b01011000,0b00010000,0b00000000}, // e
	{0b00010000,0b01111100,0b00010010,0b00000100,0b00000000}, // f
	{0b01010000,0b10101000,0b10101000,0b10011000,0b00000000}, // g
	{0b01111110,0b00001000,0b00001000,0b01110000,0b00000000}, // h
	{0b00000000,0b01001000,0b01111010,0b01000000,0b00000000}, // i
	{0b00000000,0b01000000,0b10000000,0b01111010,0b00000000}, // j
	{0b01111110,0b00010000,0b00101000,0b01000000,0b00000000}, // k
	{0b00000000,0b01000010,0b01111110,0b01000000,0b00000000}, // l
	{0b01111000,0b00010000,0b00011000,0b01110000,0b00000000}, // m
	{0b01111000,0b00001000,0b00001000,0b01110000,0b00000000}, // n
	{0b00110000,0b01001000,0b01001000,0b00110000,0b00000000}, // o
	{0b11111000,0b01001000,0b01001000,0b00110000,0b00000000}, // p
	{0b00110000,0b01001000,0b01001000,0b11111000,0b00000000}, // q
	{0b01111000,0b00001000,0b00001000,0b00010000,0b00000000}, // r
	{0b01010000,0b01011000,0b01101000,0b00101000,0b00000000}, // s
	{0b00001000,0b00111110,0b01001000,0b01000000,0b00000000}, // t
	{0b00111000,0b01000000,0b01000000,0b01111000,0b00000000}, // u
	{0b00000000,0b00111000,0b01000000,0b00111000,0b00000000}, // v
	{0b01111000,0b01100000,0b01100000,0b01111000,0b00000000}, // w
	{0b01001000,0b00110000,0b00110000,0b01001000,0b00000000}, // x
	{0b00011000,0b10100000,0b01000000,0b00111000,0b00000000}, // y
	{0b01001000,0b01101000,0b01011000,0b01001000,0b00000000}, // z
	{0b00000000,0b00001000,0b00111100,0b01000010,0b00000000}, // {
	{0b00000000,0b00000000,0b01111110,0b00000000,0b00000000}, // |
	{0b00000000,0b01000010,0b00111100,0b00001000,0b00000000}, // }
	{0b11111111,0b11111111,0b11111111,0b11111111,0b11111111}, // BLOCK
	//{0b00000100,0b00000010,0b00000100,0b00000010,0b00000000}, // ~
};

void OLED_initialize(){
	OLED_write_c(0xae);        //display  off        
	OLED_write_c(0xa1);        //segment  remap        
	OLED_write_c(0xda);        //common  pads  hardware:  alternative        
	OLED_write_c(0x12);        
	OLED_write_c(0xc8);        //common  output scan direction:com63~com0       
	OLED_write_c(0xa8);        //multiplex  ration  mode:63        
	OLED_write_c(0x3f);        
	OLED_write_c(0xd5);        //display  divide ratio/osc. freq. mode       
	OLED_write_c(0x80);                
	OLED_write_c(0x81);        //contrast  control          
	OLED_write_c(0x50);           //contrast level [0x00-0xFF]      
	OLED_write_c(0xd9);        //set  pre-charge  period    
	OLED_write_c(0x21);                    
	OLED_write_c(0x20);        //Set  Memory  Addressing  Mode        
	OLED_write_c(0x00);                
	OLED_write_c(0xdb);        //VCOM  deselect  level  mode        
	OLED_write_c(0x30);                
	OLED_write_c(0xad);        //master  configuration          
	OLED_write_c(0x00);                
	OLED_write_c(0xa4);        //out  follows  RAM  content        
	OLED_write_c(0xa6);        //set  normal  display        
	OLED_write_c(0xaf);        //  display  on 
} 

void OLED_write_c(unsigned char command) {
	volatile char *ext_OLED = (char *) OLED_COMMAND_BASE_ADDR;
	ext_OLED[0] = command;
}

void OLED_write_d(unsigned char data) {
	volatile char *ext_OLED = (char *) OLED_DATA_BASE_ADDR;
	ext_OLED[0] = data;
}

void OLED_print_char(unsigned char character) {
	volatile char *ext_OLED = (char *) OLED_DATA_BASE_ADDR;

	for (int i = 0; i < 5; i++) {
		ext_OLED[0] = pgm_read_byte(&font[character - 32][i]);
	}
}

void OLED_print_string(unsigned char* string){
	for (unsigned char i = 0; i < strlen(string); i++) {
		OLED_print_char(string[i]);
	}
}

void OLED_clear(){
	volatile char *ext_OLED = (char *) OLED_DATA_BASE_ADDR;
	for (int i = 0; i<8; i++){
		for (int f = 0; f<128;f++){
			ext_OLED[0] = 0x00;
		}
	}
}

void OLED_goto_page(unsigned char new_page){
  	OLED_write_c(0x22);
  	OLED_write_c(new_page);
  	OLED_write_c(0x07);

	page = new_page;
}

void OLED_goto_column(unsigned char new_column){
  	OLED_write_c(0x21);
	OLED_write_c(new_column);
	OLED_write_c(0x7F);

	column = new_column;
}

void OLED_goto_pos(int row, int column){
	OLED_goto_page((char)row);
	OLED_goto_column((char)column);
}

void OLED_reset_position() {
	OLED_goto_column(0x00);
	OLED_goto_page(0x00);
}

void OLED_navigate_ypos_with_joystick(int y, int lower_page_limit){
	if(y > 95){
		if(page == 0){
			OLED_goto_page(lower_page_limit);
		}else{
			OLED_goto_page(page-1);
		}
	}else if(y < -95){
		if(page == lower_page_limit){
			OLED_goto_page(0);
		}else{
			OLED_goto_page(page+1);
		}
	}
}

void OLED_navigate_xpos_with_joystick(int x){
		if(x > 90){
		if(column > 122){
			OLED_goto_column(0);
		}else{
			OLED_goto_column(column+5);
		}
	}else if(x < -90){
		if(column < 5){
			OLED_goto_column(127);
		}else{
			OLED_goto_column(column-5);
		}
	}
}

void OLED_clear_page(int pageNr){
	volatile char *ext_OLED = (char *) OLED_DATA_BASE_ADDR;
	OLED_goto_page(pageNr);
	OLED_goto_column(0);
	for (int f = 0; f<128; f++) {
		ext_OLED[0] = 0x00;
	}
}

void OLED_invert_page(int page) {
	volatile char *ext_OLED = (char *) OLED_DATA_BASE_ADDR;
	OLED_goto_page(page);
	OLED_goto_column(0);
	for (int f = 0; f<128; f++) {
		ext_OLED[0] = ~ext_OLED[0];
	}
}

void OLED_home(){
	// initialize home menu
	OLED_clear();
	OLED_print_string("git pull out");
	OLED_goto_page(1);
	OLED_goto_column(0);
	OLED_print_string("git come");
	OLED_goto_page(2);
	OLED_goto_column(0);
	OLED_print_string("git no baby");

	OLED_goto_page(0);
	OLED_goto_column(0);
	while(1){
		OLED_navigate_ypos_with_joystick(controller_joystick_read_Y(),2);
		if(page == 0){
			OLED_clear_page(page);
			_delay_ms(500);
			OLED_goto_page(0);
			OLED_goto_column(0);
			OLED_print_string("git pull out");
			_delay_ms(500);
			printf("page=0\n\r");
		}
		else if(page == 1){
			OLED_clear_page(page);
			_delay_ms(500);
			OLED_goto_page(1);
			OLED_goto_column(0);
			OLED_print_string("git come");
			_delay_ms(500);
			printf("page=1\n\r");
		}

		else if(page == 2){
			OLED_clear_page(page);
			_delay_ms(500);
			OLED_goto_page(2);
			OLED_goto_column(0);
			OLED_print_string("git no baby");
			_delay_ms(500);
			printf("page=2\n\r");
		}
		
	}
	
}