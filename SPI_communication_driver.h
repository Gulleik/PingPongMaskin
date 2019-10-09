#ifndef SPI
#define SPI

#endif

#include <avr/io.h>
#include <stdint.h>


/**
 * Initializes the SPI master.
*/
void SPI_master_initialize();

/**
 * Writes data to the SPI data bus.
 * @param data; data to be written.
*/
void SPI_write_byte(uint8_t data);

/**
 * Reads data from the SPI data bus.
 * @return data; data read from the bus.
*/
uint8_t SPI_read_byte();