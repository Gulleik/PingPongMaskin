#ifndef UART_H
#define UART_H

#define FOSC 4915200// Clock Speed in Hz
#define BAUD 9600

#include <avr/io.h>

/**
 * @file
 * @brief NODE1 UART driver
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
 * @brief Transmits data using UART interface.
 * @param data; Data to be transmitted.
*/
void UART_transmit(char data);

#endif