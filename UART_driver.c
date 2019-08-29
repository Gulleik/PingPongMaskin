#include "UART_driver.h"
#define FOSC 4915200// Clock Speed
#define BAUD 9600

#include <avr/io.h>

void UART_driver_initialize() {
	UBRRH = (unsigned char)((FOSC / 16 / BAUD - 1) >> 8);
	UBRRL = (unsigned char)(FOSC / 16 / BAUD - 1);
	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1 << URSEL0) | (3 << UCSZ00);
}

void UART_driver_transmit(unsigned int data) {

    /* Wait for empty transmit buffer */
    loop_until_bit_is_set(UCSR0A, UDRE0);;

    /* Put data into buffer, sends the data */
    UDR0 = data;

	return 0;
} 


unsigned char UART_driver_receive() {
		/* Wait for data to be received */
		loop_until_bit_is_set(UCSR0A, RXC0);
		/* Get and return received data from buffer */
		return UDR0;
}





	
