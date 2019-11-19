#ifndef SPI
#define SPI

#include <avr/io.h>
#include <stdint.h>

/**
 * @file
 * @brief NODE2 SPI driver
*/

#define DD_CS PB0
#define DD_MOSI PB2
#define DD_SCK PB1

/**
 * @brief Initialize ATmega 2560 as SPI master
*/
void SPI_master_initialize();

/**
 * @brief Write one byte on SPI bus.
 * @param data; Data to be written on SPI bus.
*/
void SPI_write_byte(uint8_t data);

/**
 * @brief Read one byte of data from SPI bus.
 * @return Data read from SPI bus.
*/
uint8_t SPI_read_byte();

#endif