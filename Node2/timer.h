#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @file
 * @brief NODE2 Driver to handle timer interrupts
*/

volatile uint8_t controller_interrupt; /** < @brief variable to check if timer_interrupt have been triggered, val = 1 if triggered */
volatile uint8_t IR_interrupt; /** < @brief variable to check if ir_timer_interrupt have been triggered, val = 1 if triggered */

/**
 * @brief Enum to differentiate timers
*/
enum TIMER {
    CONTROLLER_TIMER, IR_ADC_TIMER
} typedef timer_t;

/**
 * @brief Initialize timer interrupts
*/
void timer_initialize();

/**
 * @brief Turns on timer interrupt
 * @param timer; timer to be enabled
*/
void timer_enable(timer_t timer);

/**
 * @brief Turns off timer interrupt
 * @param timer; timer to be disabled
*/
void timer_disable(timer_t timer);

#endif