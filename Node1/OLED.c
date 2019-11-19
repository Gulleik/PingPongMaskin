#include "OLED.h"

/*Font for use in pint_char functions*/
const unsigned char PROGMEM font5[95][5] = {
	{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, //
	{0b00000000,0b00000000,0b01011111,0b00000000,0b00000000}, // !
	{0b00000000,0b00000111,0b00000000,0b00000111,0b00000000}, // "
	{0b00010100,0b01111111,0b00010100,0b01111111,0b00010100}, // #
	{0b00100100,0b00101010,0b01111111,0b00101010,0b00010010}, // $
	{0b00100011,0b00010011,0b00001000,0b01100100,0b01100010}, // %
	{0b00110110,0b01001001,0b01010101,0b00100010,0b01010000}, // &
	{0b00000000,0b00000101,0b00000011,0b00000000,0b00000000}, // '
	{0b00000000,0b00011100,0b00100010,0b01000001,0b00000000}, // (
	{0b00000000,0b01000001,0b00100010,0b00011100,0b00000000}, // )
	{0b00001000,0b00101010,0b00011100,0b00101010,0b00001000}, // *
	{0b00001000,0b00001000,0b00111110,0b00001000,0b00001000}, // +
	{0b00000000,0b01010000,0b00110000,0b00000000,0b00000000}, // ,
	{0b00001000,0b00001000,0b00001000,0b00001000,0b00001000}, // -
	{0b00000000,0b01100000,0b01100000,0b00000000,0b00000000}, // .
	{0b00100000,0b00010000,0b00001000,0b00000100,0b00000010}, // /
	{0b00111110,0b01010001,0b01001001,0b01000101,0b00111110}, // 0
	{0b00000000,0b01000010,0b01111111,0b01000000,0b00000000}, // 1
	{0b01000010,0b01100001,0b01010001,0b01001001,0b01000110}, // 2
	{0b00100001,0b01000001,0b01000101,0b01001011,0b00110001}, // 3
	{0b00011000,0b00010100,0b00010010,0b01111111,0b00010000}, // 4
	{0b00100111,0b01000101,0b01000101,0b01000101,0b00111001}, // 5
	{0b00111100,0b01001010,0b01001001,0b01001001,0b00110000}, // 6
	{0b00000001,0b01110001,0b00001001,0b00000101,0b00000011}, // 7
	{0b00110110,0b01001001,0b01001001,0b01001001,0b00110110}, // 8
	{0b00000110,0b01001001,0b01001001,0b00101001,0b00011110}, // 9
	{0b00000000,0b00110110,0b00110110,0b00000000,0b00000000}, // :
	{0b00000000,0b01010110,0b00110110,0b00000000,0b00000000}, // ;
	{0b00000000,0b00001000,0b00010100,0b00100010,0b01000001}, // <
	{0b00010100,0b00010100,0b00010100,0b00010100,0b00010100}, // =
	{0b01000001,0b00100010,0b00010100,0b00001000,0b00000000}, // >
	{0b00000010,0b00000001,0b01010001,0b00001001,0b00000110}, // ?
	{0b00110010,0b01001001,0b01111001,0b01000001,0b00111110}, // @
	{0b01111110,0b00010001,0b00010001,0b00010001,0b01111110}, // A
	{0b01111111,0b01001001,0b01001001,0b01001001,0b00110110}, // B
	{0b00111110,0b01000001,0b01000001,0b01000001,0b00100010}, // C
	{0b01111111,0b01000001,0b01000001,0b00100010,0b00011100}, // D
	{0b01111111,0b01001001,0b01001001,0b01001001,0b01000001}, // E
	{0b01111111,0b00001001,0b00001001,0b00000001,0b00000001}, // F
	{0b00111110,0b01000001,0b01000001,0b01010001,0b00110010}, // G
	{0b01111111,0b00001000,0b00001000,0b00001000,0b01111111}, // H
	{0b00000000,0b01000001,0b01111111,0b01000001,0b00000000}, // I
	{0b00100000,0b01000000,0b01000001,0b00111111,0b00000001}, // J
	{0b01111111,0b00001000,0b00010100,0b00100010,0b01000001}, // K
	{0b01111111,0b01000000,0b01000000,0b01000000,0b01000000}, // L
	{0b01111111,0b00000010,0b00000100,0b00000010,0b01111111}, // M
	{0b01111111,0b00000100,0b00001000,0b00010000,0b01111111}, // N
	{0b00111110,0b01000001,0b01000001,0b01000001,0b00111110}, // O
	{0b01111111,0b00001001,0b00001001,0b00001001,0b00000110}, // P
	{0b00111110,0b01000001,0b01010001,0b00100001,0b01011110}, // Q
	{0b01111111,0b00001001,0b00011001,0b00101001,0b01000110}, // R
	{0b01000110,0b01001001,0b01001001,0b01001001,0b00110001}, // S
	{0b00000001,0b00000001,0b01111111,0b00000001,0b00000001}, // T
	{0b00111111,0b01000000,0b01000000,0b01000000,0b00111111}, // U
	{0b00011111,0b00100000,0b01000000,0b00100000,0b00011111}, // V
	{0b01111111,0b00100000,0b00011000,0b00100000,0b01111111}, // W
	{0b01100011,0b00010100,0b00001000,0b00010100,0b01100011}, // X
	{0b00000011,0b00000100,0b01111000,0b00000100,0b00000011}, // Y
	{0b01100001,0b01010001,0b01001001,0b01000101,0b01000011}, // Z
	{0b00000000,0b00000000,0b01111111,0b01000001,0b01000001}, // [
	{0b00000010,0b00000100,0b00001000,0b00010000,0b00100000}, // "\"
	{0b01000001,0b01000001,0b01111111,0b00000000,0b00000000}, // ]
	{0b00000100,0b00000010,0b00000001,0b00000010,0b00000100}, // ^
	{0b01000000,0b01000000,0b01000000,0b01000000,0b01000000}, // _
	{0b00000000,0b00000001,0b00000010,0b00000100,0b00000000}, // `
	{0b00100000,0b01010100,0b01010100,0b01010100,0b01111000}, // a
	{0b01111111,0b01001000,0b01000100,0b01000100,0b00111000}, // b
	{0b00111000,0b01000100,0b01000100,0b01000100,0b00100000}, // c
	{0b00111000,0b01000100,0b01000100,0b01001000,0b01111111}, // d
	{0b00111000,0b01010100,0b01010100,0b01010100,0b00011000}, // e
	{0b00001000,0b01111110,0b00001001,0b00000001,0b00000010}, // f
	{0b00001000,0b00010100,0b01010100,0b01010100,0b00111100}, // g
	{0b01111111,0b00001000,0b00000100,0b00000100,0b01111000}, // h
	{0b00000000,0b01000100,0b01111101,0b01000000,0b00000000}, // i
	{0b00100000,0b01000000,0b01000100,0b00111101,0b00000000}, // j
	{0b00000000,0b01111111,0b00010000,0b00101000,0b01000100}, // k
	{0b00000000,0b01000001,0b01111111,0b01000000,0b00000000}, // l
	{0b01111100,0b00000100,0b00011000,0b00000100,0b01111000}, // m
	{0b01111100,0b00001000,0b00000100,0b00000100,0b01111000}, // n
	{0b00111000,0b01000100,0b01000100,0b01000100,0b00111000}, // o
	{0b01111100,0b00010100,0b00010100,0b00010100,0b00001000}, // p
	{0b00001000,0b00010100,0b00010100,0b00011000,0b01111100}, // q
	{0b01111100,0b00001000,0b00000100,0b00000100,0b00001000}, // r
	{0b01001000,0b01010100,0b01010100,0b01010100,0b00100000}, // s
	{0b00000100,0b00111111,0b01000100,0b01000000,0b00100000}, // t
	{0b00111100,0b01000000,0b01000000,0b00100000,0b01111100}, // u
	{0b00011100,0b00100000,0b01000000,0b00100000,0b00011100}, // v
	{0b00111100,0b01000000,0b00110000,0b01000000,0b00111100}, // w
	{0b01000100,0b00101000,0b00010000,0b00101000,0b01000100}, // x
	{0b00001100,0b01010000,0b01010000,0b01010000,0b00111100}, // y
	{0b01000100,0b01100100,0b01010100,0b01001100,0b01000100}, // z
	{0b00000000,0b00001000,0b00110110,0b01000001,0b00000000}, // {
	{0b00000000,0b00000000,0b01111111,0b00000000,0b00000000}, // |
	{0b00000000,0b01000001,0b00110110,0b00001000,0b00000000}, // }
	{0b00000010,0b00000001,0b00000011,0b00000010,0b00000001}, // ~
	};

/*************************************************************
 * WRITE
*************************************************************/
void OLED_write_c(uint8_t command) {
	/*Write to OLED command*/
	volatile uint8_t *ext_OLED = (uint8_t *) OLED_COMMAND_BASE_ADDR;
	ext_OLED[0] = command;
}

void OLED_write_d(uint8_t data) {
	/*Write new data to SRAM memory*/
	volatile uint8_t *ext_OLED_mem = (uint8_t *) SRAM_OLED_BASE_ADDR;
	ext_OLED_mem[current_page * 128 + current_column] = data;

	/*Update current_column and current_page variables*/
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

void OLED_append_d(uint8_t data, uint8_t inverted) {
	/*Append new data to SRAM memory*/
	uint8_t *ext_OLED_mem = (uint8_t *) SRAM_OLED_BASE_ADDR;
	if (inverted) {
		ext_OLED_mem[current_page * 128 + current_column] ^= data;
	} else {
		ext_OLED_mem[current_page * 128 + current_column] |= data;
	}

	/*Update current_column and current_page variables*/
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


/*************************************************************
 * INIT
*************************************************************/
void OLED_initialize(uint8_t refresh_rate){
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
	
	/*Initialize timer with interrupt rate as specified refresh_rate*/
    timer_initialize(refresh_rate);

    OLED_clear();
}


/*************************************************************
 * PRINT
*************************************************************/
void OLED_set_pixel(uint8_t x_pos, uint8_t y_pos, uint8_t inverted) {
	uint8_t value = (1 << (y_pos % 8));
	
	OLED_goto_page(y_pos / 8);
	OLED_goto_column(x_pos);
	OLED_append_d(value, inverted);
}

void OLED_print_char(char character) {
	/*Using font defined in fonts.h, write specified charater to current page and column*/
	for (uint8_t i = 0; i < 5; i++) {
		OLED_write_d(pgm_read_byte(&font5[character - 32][i]));
	}
}

void OLED_print_string(char* string){
	/*Loop through input string and print each separate character at current page and column*/
	for (uint8_t i = 0; i < strlen(string); i++) {
		OLED_print_char(string[i]);
	}
}

void OLED_print_string_P(const char* string){
	/*Loop through input string and print each separate character at current page and column*/
	while (pgm_read_byte(string) != 0x00) {
		OLED_print_char(pgm_read_byte(string++));
	}
}

void OLED_print_char_inverted(char character) {
	/*Using font defined in fonts.h, invert specified charater and write to current page and column*/
	for (uint8_t i = 0; i < 5; i++) {
		OLED_write_d(~pgm_read_byte(&font5[character - 32][i]));
	}
}

void OLED_print_string_inverted(char* string){
	/*Loop through input string, invert and print each separate character at current page and column*/
	for (uint8_t i = 0; i < strlen(string); i++) {
		OLED_print_char_inverted(string[i]);
	}
}

void OLED_print_string_inverted_P(const char* string){
	/*Loop through input string and print each separate character at current page and column*/
	while (pgm_read_byte(string) != 0x00) {
		OLED_print_char_inverted(pgm_read_byte(string++));
	}
}


/*************************************************************
 * NAVIGATION 
*************************************************************/
void OLED_goto_page(uint8_t new_page){
	/*Set page start and end address*/
  	OLED_write_c(0x22);
  	OLED_write_c(new_page);
  	OLED_write_c(0x07);

	/*Update cuurent_page*/
	current_page = new_page;
}

void OLED_goto_column(uint8_t new_column){
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
	for (uint8_t i = 0; i<8; i++){
		for (uint8_t f = 0; f<128;f++){
			OLED_write_d(0x00);
		}
	}
	// uint8_t *ext_OLED_mem = (uint8_t *) SRAM_OLED_BASE_ADDR;
	// for (uint8_t i = 0; i<8; i++){
	// 	for (uint8_t f = 0; f<128;f++){
	// 		printf("p: %d, c: %d, SRAM data: %d\n\r", i, f, ext_OLED_mem[i * 128 + f]);
	// 	}
	// }
}

void OLED_clear_page(uint8_t page){
	OLED_goto_page(page);
	OLED_goto_column(0);
	/*Set value of all bytes on one line to 0 -> Clear line*/
	for (uint8_t f = 0; f<128; f++) {
		OLED_write_d(0);
	}
}

void OLED_invert_page(uint8_t page) {
	uint8_t *ext_OLED_mem = (uint8_t *) SRAM_OLED_BASE_ADDR;
	OLED_goto_page(page);
	OLED_goto_column(0);
	/*Access OLED address in SRAM to read set value and print values inverted*/
	for (uint8_t f = 0; f<128; f++) {
		OLED_write_d(~ext_OLED_mem[page * 128 + f]);
	}
}

/*************************************************************
 * REFRESH
*************************************************************/
void OLED_refresh_enable() {
    /*Enable timer by enabling interrupts*/
    TIMSK |= (1 << OCIE1A);
}

void OLED_freeze_image() {
    /*Disable timer by disabling interrupts*/
    TIMSK &= ~(1 << OCIE1A);
}

void OLED_update_image() {
	uint8_t *ext_OLED_mem = (uint8_t *) SRAM_OLED_BASE_ADDR;
	uint8_t *ext_OLED = (uint8_t *) OLED_DATA_BASE_ADDR;
	uint8_t temp_col = current_column;
	uint8_t temp_page = current_page;
	OLED_reset_position();
	for (int page = 0; page<8; page++){
		for (int column = 0; column<128; column++){
			ext_OLED[0] = ext_OLED_mem[page * 128 + column];
		}
	}
	current_column = temp_col;
	current_page = temp_page;
}

ISR (TIMER1_COMPA_vect) {
	//ISR for timer1, used for screen refresh
    OLED_update_image();
}

ISR (TIMER1_OVF_vect);