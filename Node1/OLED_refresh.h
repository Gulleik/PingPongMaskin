#ifndef TIMER_H
#define TIMER_H


#include <stdint.h>

void OLED_refresh_initialize(uint8_t refresh_rate);

void OLED_refresh_enable();

void OLED_freeze_image();

#endif