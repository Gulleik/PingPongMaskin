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

/**
 * Structure with command initializations of OLED
*/
void OLED_initialize();

/**
 * Write command to OLED_command
 * @param command; char-value to be written to OLED_command register
*/
void OLED_write_c(unsigned char command);

/**
 * Write data to OLED_data
 * @param data; char-value to be written to OLED_data register
*/
void OLED_write_d(unsigned char data);

/**
 * Print character to current line and column of OLED screen
 * @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_char(unsigned char character);

/**
 * Print string to current line and column of OLED screen
 * @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_string(unsigned char* string);

/**
 * Clears entire OLED screen
*/
void OLED_clear();

/**
 * Sets the cursor location to the given page (row), 0 corresponding to the top row and to 7 corresponding to the bottom row.
 * @param new_page; The cursor is set to this page (row). Must be between 0 and 7 (inclusively).
*/
void OLED_goto_page(unsigned char new_page);

/**
 * Set the cursor location to the given column, 0 corresponding to the left-most column and 127 corresponding to the right-most column.
 * @param new_column; The cursor is set to this column. Must be between 0 and 127 (inclusively)
*/
void OLED_goto_column(unsigned char new_column);

/**
 * Sets the cursor to the location given by row and column.
 * @param row; Cursor is set to this row. Must be between 0 and 7 (inclusively).
 * @param column; Cursor is set to this column. Must be between 0 and 127 (inclusively).
*/
void OLED_goto_pos(int row, int column);

/**
 * Sets cursor location to upper-left corner; row 0 and column 0.
*/
void OLED_reset_position();

/**
 * Set Y-position on OLED with joystick. One movement equals one char size (8X5 pixels)
 * @param x; Y position on joystick
 * @param lower_page_limit; Lower limit of Ypos (for menus)
*/
void OLED_navigate_ypos_with_joystick(int y, int lower_page_limit);

/**
 * Set X-position on OLED with joystick. One movement equaks one char size (8X5 pixels)
 * @param x; X position on joystick
*/
void OLED_navigate_xpos_with_joystick(int x);

/**
 * Clears an entire page
 * @param pageNr; Page to be cleared
*/
void OLED_clear_page(int pageNr);

/**
 * *************UNTESTED**************
 * /brief Inverts an entire page
 * 
 * @param page; Page to be inverted
*/
void OLED_invert_page(int page);

/**
 * Fetches / creates main menu and lets you scrool through it.
*/
void OLED_home();