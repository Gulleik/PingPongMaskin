#ifndef OLED_H
#define OLED_H

#define F_CPU 4915200 // clock frequency in Hz

#include <util/delay.h>
#include <avr/pgmspace.h>
#include "XMEM.h"
#include "timer.h"

/**
 * @file
 * @brief NODE1 OLED driver
*/

/**
 * @brief Variable for keeping track of column position on screen when writing OLED data to SRAM
*/
volatile uint8_t current_column;

/**
 * @brief Variable for keeping track of page position on screen when writing OLED data to SRAM
*/
volatile uint8_t current_page;

/**
  @brief Runs several commands to initialize the OLED (screen is cleared).
  @param refresh_rate; The refresh rate of the OLED screen.
*/
void OLED_initialize(uint8_t refresh_rate);

/**
 * @brief Set value of one pixel to 1
 * @param pos_x; X position of the pixel.
 * @param pos_y; Y position of the pixel.
 * @param inverted; Specifies whether bit should be set or inverted. If inverted != 0, invert pixel. Else set pixel to 1.
*/
void OLED_set_pixel(uint8_t pos_x, uint8_t pos_y, uint8_t inverted);

/**
  @brief Write data to OLED_data register using dual buffering. Data is saved to address space 0x1c00-0x2000 (?) of SRAM.
  @param data; Value to be written to OLED_data register.
*/
void OLED_write_d(uint8_t data);

/**
 * @brief Iterate through entire address space of OLED screen in SRAM and rewrite everything exactly once
*/
void OLED_update_image();

/**
  @brief Print string to current line and column of OLED screen
  @param string; Pointer to string in internal memory
*/
void OLED_print_string(char* string);

/**
 * @brief Print PROGMEM string to current line and column of OLED screen
 * @param string; PROGMEM pointer to string in FLASH memory
*/
void OLED_print_string_P(const char* string);

/**
  @brief Print inverted string to current line and column of OLED screen
  @param string; String to be printed, has to be in double exclamation marks. => ""
*/
void OLED_print_string_inverted(char* string);

/**
 * @brief Print PROGMEM string to current line and column of OLED screen
 * @param string; PROGMEM pointer to string in FLASH memory
*/
void OLED_print_string_inverted_P(const char* string);

/**
 * @brief Clear entire OLED screen, i.e. pages 0-7
*/
void OLED_clear();

/**
 * @brief Set current page for OLED_write_d operations
 * @param new_page; Specifies what to set current page to. Must be in range 0-7.
*/
void OLED_goto_page(uint8_t new_page);

/**
 * @brief Set current column for OLED_write_d operations
 * @param new_column; Specifies what to set current column to. Must be in range 0-127.
*/
void OLED_goto_column(uint8_t new_column);

/**
 * @brief Set both current column and current page for OLED_write_d operations to 0
*/
void OLED_reset_position();

/**
  @brief Clears an entire page
  @param page; Page to be cleared
*/
void OLED_clear_page(uint8_t page);

/**
 * @brief Inverts an entire page
 * @param page; Page to be inverted
*/
void OLED_invert_page(uint8_t page);

/**
 * @brief Enable timer to keep refresing image at refresh rate specified in initializer.
*/
void OLED_refresh_enable();

/**
 * @brief Freeze image by disabling refresh timer.
*/
void OLED_freeze_image();

#endif