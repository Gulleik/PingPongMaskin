#ifndef SPI
#define SPI

#include <avr/io.h>
#include <stdint.h>

/**
 * @file
 * @brief SPI driver NODE1
*/

/**
 * @brief Initialize ATmega 2560 as SPI master
*/
void SPI_master_initialize();

/**
 * @brief Write one byte on SPI bus.
 * @param data; One byte of data
*/
void SPI_write_byte(uint8_t data);

/**
 * @brief Read one byte of data from SPI bus.
 * @return One byte of data
*/
uint8_t SPI_read_byte();

#endif