#ifndef UART_H
#define UART_H

#define FOSC 4915200// Clock Speed in Hz
#define BAUD 9600

#include <avr/io.h>

/**
 * @file
 * @brief UART driver NODE1
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
 * @brief Initialize UART hardware
*/
void UART_transmit(char data);

#endif