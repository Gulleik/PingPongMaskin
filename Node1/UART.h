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
 * Initialize UART hardware
*/
void UART_transmit(char data);