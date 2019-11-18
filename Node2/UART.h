#ifndef UART_H
#define UART_H

#include <avr/io.h>

/**
 * @file
 * @brief UART driver NODE2
*/

/**
 * @brief Initialize UART hardware
*/
void UART_initialize();

/**
 * @brief Listen to UART interface and recieve data
 * @return Recieved data
*/
unsigned char UART_receive();

/**
 * @brief Transmit data
 * @param data; Data to be transmitted.
*/
void UART_transmit(char data);

#endif