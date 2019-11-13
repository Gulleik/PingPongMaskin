#ifndef OLED_H
#define OLED_H


#include "string.h"
#include "lib.h"
#include <stdint.h>

static uint8_t current_column;
static uint8_t current_page;

/**
  @brief Structure with command initializations of OLED
*/
void OLED_initialize();

/**
  @brief Write command to OLED_command
  @param command; Char value to be written to OLED_command register
*/
void OLED_write_c(unsigned char command);

/**
  @brief Write data to OLED_data using dual buffering. Data is saved to address space 0x1c00-0x2000 (?) of SRAM
  @param data; Char value to be written to OLED_data register
*/
void OLED_write_d(unsigned char data);

/**
  @brief Print character to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_char(unsigned char character);

/**
  @brief Print string to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_string(unsigned char* string);

/**
  @brief Print inverted character to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_char_inverted(unsigned char character);

/**
  @brief Print inverted string to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_string_inverted(unsigned char* string);

/**
 * @brief Clear entire OLED screen, i.e. pages 0-7
*/
void OLED_clear();

/**
 * @brief Set current page for OLED_write_d operations
*/
void OLED_goto_page(unsigned char new_page);

/**
 * @brief Set current column for OLED_write_d operations
*/
void OLED_goto_column(unsigned char new_column);

/**
 * @brief Set both current column and current page for OLED_write_d operations to 0
*/
void OLED_reset_position();

/**
 * @brief Set both current column and current page for OLED_write_d operation to input values
 * @param row; Current row to be set
 * @param column; Current column to be set
*/
void OLED_pos(int row, int column);

/**
  @brief Set X-position on OLED with joystick. One movement equaks one char size (8X5 pixels)
  @param x; X position on joystick
*/
void OLED_navigate_Xpos_with_joystick(int x);

/**
  @brief Set Y-position on OLED with joystick. One movement equals one char size (8X5 pixels)
  @param x; Y position on joystick
  @param lower_page_limit; Lower limit of Ypos (for menus)
*/
void OLED_navigate_Ypos_with_joystick(int y, int lower_page_limit);


/**
  @brief Clears an entire page
  @param pageNR; Page to be cleared
*/
void OLED_clear_page(int page);

/**
 * @brief Inverts an entire page
 * @param page; Page to be inverted
*/
void OLED_invert_page(int page);

/*
 * Display screensaver
*//*
void OLED_screensaver()*/

#endif