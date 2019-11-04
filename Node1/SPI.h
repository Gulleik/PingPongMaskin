#ifndef SPI
#define SPI

#endif

#include <avr/io.h>
#include <stdint.h>


void SPI_master_initialize();

void SPI_write_byte(uint8_t data);

uint8_t SPI_read_byte();