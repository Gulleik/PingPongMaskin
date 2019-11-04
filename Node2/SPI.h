#ifndef SPI
#define SPI

#endif

#include <avr/io.h>
#include <stdint.h>

#define DD_CS PB0
#define DD_MOSI PB2
#define DD_SCK PB1

/**
 * Initialize ATmega 2560 as SPI master
*/
void SPI_master_initialize();

/**
 * write one byte on SPI bus.
 * @param data; one byte of data
*/
void SPI_write_byte(uint8_t data);

/**
 * read one byte of data from SPI bus.
 * @return one byte of data
*/
uint8_t SPI_read_byte();