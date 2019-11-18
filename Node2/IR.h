#ifndef IR_H
#define IR_H


#include <stdint.h>

/**
 * @file
 * @brief IR driver
*/


int8_t is_blocked; /** @brief Status of IR sensor */


/**
 * @brief Initialize IR sensor at ADC1.
*/
void IR_internal_ADC_initialize();

/**
 * @brief Read once from the ADC connected to the IR.
*/
void IR_internal_ADC_read();

#endif