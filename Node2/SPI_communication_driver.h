#ifndef SPI
#define SPI

#endif

#include <avr/io.h>
#include <stdint.h>

#define DDR_SPI DDRB
#define DD_CS PB0
#define DD_MOSI PB2
#define DD_SCK PB1


void SPI_master_initialize();

void SPI_write_byte(uint8_t data);

uint8_t SPI_read_byte();