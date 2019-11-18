#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * @brief seconds passed since game timer enabled
*/
uint16_t time;

/**
 * @brief initialize game timer normally and OLED timer with specified refresh rate
 * @param refresh_rate; Requested refresh rate of OLED screen
*/
void timer_initialize(uint8_t refresh_rate);

/**
 * @brief Enable game timer
*/
void timer_game_enable();

/**
 * @brief Disable game timer
*/
void timer_game_disable();

#endif