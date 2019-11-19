#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <stdint.h>

/**
 * @file
 * @brief NODE1 SPI driver
*/

/**
 * @brief Initialize ATmega 2560 as SPI master
*/
void SPI_master_initialize();

/**
 * @brief Write one byte on SPI bus.
 * @param data; Data to be written onto SPI bus.
*/
void SPI_write_byte(uint8_t data);

/**
 * @brief Read one byte of data from SPI bus.
 * @return Returns the data read from the SPI bus.
*/
uint8_t SPI_read_byte();

#endif