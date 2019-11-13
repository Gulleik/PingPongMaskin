#ifndef UART_H
#define UART_H


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