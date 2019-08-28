#include "UART_driver.h"

#include <avr/io.h>

void UART_driver_receive() {
    
}

void UART_driver_transmit(unsigned int data) {
    UCSR0B = (1 << TXEN0);

    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );

    /* Put data into buffer, sends the data */
    UDR0 = data;
} 