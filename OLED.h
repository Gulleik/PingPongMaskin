#ifndef OLED_H
#define OLED_H
#endif

#include "string.h"
void OLED_initialize();

void OLED_write_c(unsigned char command);

void OLED_write_d(unsigned char data);
void OLED_print_char(unsigned char character);
void OLED_print_string(unsigned char* string);

void OLED_clear();
void OLED_home();
void OLED_goto_line(unsigned char line);
void OLED_goto_column(unsigned char column);
void OLED_reset_position();
void OLED_pos(int row, int column);