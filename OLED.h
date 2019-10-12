#ifndef OLED_H
#define OLED_H
#endif

#include "string.h"
#include "lib.h"
#include <stdint.h>

// Char that light all pixels in a char space
#define BLOCK 126

// current page
static int page = 0;

// current column
static int column = 0;

static uint8_t current_column;
static uint8_t current_page;


/**
  Structure with command initializations of OLED
*/
void OLED_initialize();

/**
  Write command to OLED_command
  @param command; char-value to be written to OLED_command register
*/
void OLED_write_c(unsigned char command);

/**
  Write data to OLED_data
  @param data; char-value to be written to OLED_data register
*/
void OLED_write_d(unsigned char data);

/**
  Print character to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_char(unsigned char character);

/**
  Print string to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_string(unsigned char* string);

void OLED_clear();

/**
  Fetches / creates main menu and lets you scrool through it.
*/
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
  Set Y-position on OLED with joystick. One movement equals one char size (8X5 pixels)
  @param x; Y position on joystick
  @param lower_page_limit; Lower limit of Ypos (for menus)
*/
void OLED_navigate_Ypos_with_joystick(int y, int lower_page_limit);


/**
  Clears an entire page
  @param pageNR; Page to be cleared
*/
void OLED_clear_page(int pageNr);

/**
 * *************UNTESTED**************
 * /brief Inverts an entire page
 * 
 * @param page; Page to be inverted
*/
void OLED_invert_page(int page);

void OLED_home();