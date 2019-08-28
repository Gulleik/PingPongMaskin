#include "UART_driver.h"
#define FOSC 4915200// Clock Speed
#define BAUD 9600

#include <avr/io.h>

void UART_driver_transmit(unsigned int data) {
    UCSR0B = (1 << TXEN0);

    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );

    /* Put data into buffer, sends the data */
    UDR0 = data;
} 


unsigned char UART_driver_receive() {
		/* Wait for data to be received */
		while (!(UCSRA & (1 << RXC)));
		/* Get and return received data from buffer */
		return UDR;
}


void UART_driver_initialize() {
	UBRRH = (unsigned char)((FOSC / 16 / BAUD - 1) >> 8);
	UBRRL = (unsigned char)(FOSC / 16 / BAUD - 1);
	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}


	
