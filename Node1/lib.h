#ifndef LIB_H
#define LIB_H

#define OLED_COMMAND_BASE_ADDR 0x1000
#define OLED_DATA_BASE_ADDR 0x1200
#define ADC_BASE_ADDR 0x1400
#define SRAM_BASE_ADDR 0x1800
#define SRAM_OLED_BASE_ADDR 0x1c00

#endif

/**
 * Tests that SRAM is connected properly and operational.
*/
void SRAM_test(void);