
#ifndef ADC_H
#define ADC_H

#define ADC_BASE_ADDR 0x1400

#define F_CPU 4915200 //Clock frequency in HZ

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

/**
 * @file
 * @brief NODE1 ADC driver for controller input
*/

/**
 * @brief Listen to data bus and receive converted data
 * @param channel; ADC-channel to be read from
 * @return Returns the data recieved
*/
uint8_t ADC_read(uint8_t * channel);


#endif