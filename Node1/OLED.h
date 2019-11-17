#ifndef OLED_H
#define OLED_H


#include "string.h"
#include "lib.h"
#include <stdint.h>

/**
 * @file
 * @brief OLED driver
*/


static uint8_t current_column;
static uint8_t current_page;

/**
  @brief Structure with command initializations of OLED
*/
void OLED_initialize();

/**
  @brief Write data to OLED_data using dual buffering. Data is saved to address space 0x1c00-0x2000 (?) of SRAM
  @param data; Char value to be written to OLED_data register
*/
void OLED_write_d(unsigned char data);

void OLED_update_image();

/**
  @brief Print string to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_string(unsigned char* string);

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
  @brief Clears an entire page
  @param pageNR; Page to be cleared
*/
void OLED_clear_page(int page);

/**
 * @brief Inverts an entire page
 * @param page; Page to be inverted
*/
void OLED_invert_page(int page);



#endif