#include <stdint.h>

#ifndef ADC_H
#define ADC_H

/**
 * @file
 * @brief ADC driver for controller input
*/

/**
 * @brief Listen to data BUS and recieve converted ADC data
 * @param channel; ADC-channel to be read from
 * @return Recieved data
*/

char ADC_read(uint8_t * channel);


#endif