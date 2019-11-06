#include "UART.h"
#define FOSC 16000000// Clock Speed
#define BAUD 9600

#include <avr/io.h>

void UART_initialize() {
	UBRR0H = (unsigned char)((FOSC / 16 / BAUD - 1) >> 8);
	UBRR0L = (unsigned char)(FOSC / 16 / BAUD - 1);
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	fdevopen(UART_transmit, UART_receive);
}

unsigned char UART_receive() {
	/* Wait for data to be received */
	loop_until_bit_is_set(UCSR0A, RXC0);
	/* Get and return received data from buffer */
	return UDR0;
}

void UART_transmit(char data) {

    /* Wait for empty transmit buffer */
    loop_until_bit_is_set(UCSR0A, UDRE0);

    /* Put data into buffer, sends the data */
    UDR0 = data;
} 




	
