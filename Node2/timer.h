#ifndef TIMER_H
#define TIMER_H


#include <stdint.h>
volatile extern uint8_t timer_interrupt;


enum TIMER {
    CONTROLLER_TIMER, IR_ADC_TIMER
} typedef timer_t;

void timer_initialize();

void timer_enable(timer_t timer);

void timer_disable(timer_t timer);

#endif