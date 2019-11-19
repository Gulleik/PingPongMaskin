#ifndef IR_H
#define IR_H

#include "CAN.h"

/**
 * @file
 * @brief NODE2 IR driver
*/

/** 
 * @brief Status of IR sensor
*/
int8_t is_blocked;

/**
 * @brief Initialize IR sensor at ADC1.
*/
void IR_internal_ADC_initialize();

/**
 * @brief Read once from the ADC connected to the IR.
*/
void IR_internal_ADC_read();

#endif