
#include "OLED.h"
#include "UART.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "controller.h"
#include "fonts.h"

void OLED_write_c(unsigned char command) {
	/*Write to OLED command*/
	volatile char *ext_OLED = (char *) OLED_COMMAND_BASE_ADDR;
	ext_OLED[0] = command;
}

void OLED_write_d(unsigned char data) {
	/*Write to OLED data and dual buffer to SRAM*/
	volatile char *ext_OLED = (char *) OLED_DATA_BASE_ADDR;
	volatile char *ext_OLED_mem = (char *) SRAM_OLED_BASE_ADDR;
	ext_OLED[0] = data;
	ext_OLED_mem[current_page * 128 + current_column] = data;

	/*Update current coumn and current_page variables*/
	if (current_column < 127) {
		current_column++;
	} else {
		current_column = 0;
		current_page++;
	}
	if (current_page > 7) {
		current_page = 0;
	}
}

void OLED_initialize(){
	/*Display off*/
	OLED_write_c(0xae); 

	/*Segment remap*/       
	OLED_write_c(0xa1); 

	/*Common pads hardware: Alternative*/     
	OLED_write_c(0xda);      
	OLED_write_c(0x12);     

	/*Common output scan direction: com63-com0*/
	OLED_write_c(0xc8); 

	/*Multiplex ration mode: 63*/   
	OLED_write_c(0xa8);       
	OLED_write_c(0x3f);        

	/*Display divide ratio/osc. freq. mode*/
	OLED_write_c(0xd5);     
	OLED_write_c(0x80);                
	
	/*Contrast control: Contrast level 0x50 (range 0x00-0xFF)*/
	OLED_write_c(0x81);   
	OLED_write_c(0x50);  
	
	/*Set pre-charge period*/
	OLED_write_c(0xd9); 
	OLED_write_c(0x21);                    
	
	/*Set memory addressing mode*/
	OLED_write_c(0x20);       
	OLED_write_c(0x00);                
	
	/*VCOM deselect level mode*/
	OLED_write_c(0xdb);      
	OLED_write_c(0x30);                
	
	/*Master configuration*/
	OLED_write_c(0xad);          
	OLED_write_c(0x00);                
	
	/*Out follows RAM content*/
	OLED_write_c(0xa4);    
	
	/*Set normal display*/
	OLED_write_c(0xa6);       
	
	/*Display on*/
	OLED_write_c(0xaf);
	
    OLED_reset_position();
    OLED_clear();
} 

void OLED_print_char(unsigned char character) {
	/*Using font defined in fonts.h, write specified charater to current page and column*/
	for (int i = 0; i < 5; i++) {
		OLED_write_d(pgm_read_byte(&font5[character - 32][i]));
	}
}

void OLED_print_string(unsigned char* string){
	/*Loop through input string and print each separate character at current page and column*/
	for (unsigned char i = 0; i < strlen(string); i++) {
		OLED_print_char(string[i]);
	}
}

void OLED_print_char_inverted(unsigned char character) {
	/*Using font defined in fonts.h, invert specified charater and write to current page and column*/
	for (int i = 0; i < 5; i++) {
		OLED_write_d(~pgm_read_byte(&font5[character - 32][i]));
	}
}

void OLED_print_string_inverted(unsigned char* string){
	/*Loop through input string, invert and print each separate character at current page and column*/
	for (unsigned char i = 0; i < strlen(string); i++) {
		OLED_print_char_inverted(string[i]);
	}
}

void OLED_goto_page(unsigned char new_page){
	/*Set page start and end address*/
  	OLED_write_c(0x22);
  	OLED_write_c(new_page);
  	OLED_write_c(0x07);

	/*Update cuurent_page*/
	current_page = new_page;
}

void OLED_goto_column(unsigned char new_column){
	/*Set column start and end address*/
  	OLED_write_c(0x21);
	OLED_write_c(new_column);
	OLED_write_c(0x7F);

	/*Update current_column*/
	current_column = new_column;
}

void OLED_reset_position() {
	OLED_goto_column(0x00);
	OLED_goto_page(0x00);
}

void OLED_clear(){
	OLED_reset_position();
	/*Set value of all bytes on screen to 0 -> Clear all*/
	for (int i = 0; i<8; i++){
		for (int f = 0; f<128;f++){
			OLED_write_d(0x00);
		}
	}
}

void OLED_clear_page(int page){
	OLED_goto_page(page);
	OLED_goto_column(0);
	/*Set value of all bytes on one line to 0 -> Clear line*/
	for (int f = 0; f<128; f++) {
		OLED_write_d(0);
	}
}

void OLED_invert_page(int page) {
	volatile char *ext_OLED_mem = (char *) SRAM_OLED_BASE_ADDR;
	OLED_goto_page(page);
	OLED_goto_column(0);
	/*Access OLED address in SRAM to read set value and print values inverted*/
	for (int f = 0; f<128; f++) {
		OLED_write_d(~ext_OLED_mem[page * 128 + f]);
	}
}

/*
const char ss0[] = "";
const char ss1[] = "`-:-.   ,-;*`-:-.   ,-;*";
const char ss2[] = "   `=`,'=/     `=`,'=/  ";
const char ss3[] = "     y==/        y==/   ";
const char ss4[] = "   ,=,-<=`.    ,=,-<=`. ";
const char ss5[] = ",-'-'   `-=_,-'-'   `-=_";
const char ss6[] = "";
const char ss7[] = "";

char* ScreenSaver[] = {
	ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7,
};

void OLED_screensaver() {
	char c = UART_receive();
	OLED_clear();
	for (int i = 1; i <= 5; i++) {
		OLED_goto_page(i);
		OLED_goto_column(0);
		OLED_print_string(ScreenSaver[i]);
	}
	while (c != 13) {//While enter not pressed
	}
}*/