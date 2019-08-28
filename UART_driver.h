#include <avr/io.h>
#include <driver

void UART_driver_initialize();

unsigned char UART_driver_receive_data();

void UART_driver_transmit_data();