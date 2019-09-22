#ifndef OLED_H
#define OLED_H
#endif

#include "string.h"

// Char that light all pixels in a char space
#define BLOCK 126

// current page
static int page = 0;

// current column
static int column = 0;



void OLED_initialize();

void OLED_write_c(unsigned char command);

void OLED_write_d(unsigned char data);
void OLED_print_char(unsigned char character);
void OLED_print_string(unsigned char* string);

void OLED_clear();
void OLED_home();
void OLED_goto_page(unsigned char new_page);
void OLED_goto_column(unsigned char new_column);
void OLED_reset_position();

void OLED_pos(int row, int column);

/**
  Set X-position on OLED with joystick. One movement equaks one char size (8X5 pixels)
  @param x; X position on joystick
*/
void OLED_navigate_Xpos_with_joystick(int x);

/**
  Set Y-position on OLED with joystick. One movement equaks one char size (8X5 pixels)
  @param x; Y position on joystick
*/
void OLED_navigate_Ypos_with_joystick(int y);

/**
  Navigate menu in Y direction with joystick. One movement equaks one char size (8X5 pixels)
  @param x; Y position on joystick
*/
void OLED_navigate_menu();

/**
  Fetches / creates main menu
*/
void OLED_get_main_menu();
