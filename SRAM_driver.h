#include <avr/io.h>

void SRAM_driver_initialize();

void SRAM_driver_write(unsigned int uiAddress, unsigned char ucData);

unsigned char SRAM_drier_read(unsigned int uiAddress);

void SRAM_test(void);

void write(unsigned int uiAddress, unsigned char ucData);