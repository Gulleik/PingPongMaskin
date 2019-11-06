#ifndef UART_H
#define UART_H

#endif

/**
 * Initialize UART hardware
*/
void UART_initialize();

/**
 * Listen to UART interface and recieve data
 * @return recieved data
*/
unsigned char UART_receive();

/**
 * Transmit data
 * @param data; data to be transmitted.
*/
void UART_transmit(char data);