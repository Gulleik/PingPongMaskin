#ifndef OLED_H
#define OLED_H
#endif

#include "string.h"
void OLED_initialize();

void OLED_write_c(char c);

void OLED_write_d(unsigned char data);
void OLED_write_char(char *c);

void OLED_reset();
void OLED_home();
void OLED_goto_line(char line);
void OLED_goto_column(char column);
void OLED_clear_line(int line);
void OLED_pos(int row, int column);
void OLED_print(char* text);