#ifndef XMEM_H
#define XMEM_H

#define OLED_COMMAND_BASE_ADDR 0x1000
#define OLED_DATA_BASE_ADDR 0x1200
#define SRAM_BASE_ADDR 0x1800
#define SRAM_OLED_BASE_ADDR 0x1c00

#include <avr/io.h>
#include <stdint.h>

/**
 * @file
 * @brief Driver for external memory functionality
*/

// /**
//  * @brief Initialize communication with external memory
// */
// void XMEM_initialize()

/**
 * @brief Tests that SRAM is connected properly and operational.
*/
void SRAM_test(void);

#endif