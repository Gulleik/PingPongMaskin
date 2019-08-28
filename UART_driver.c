#include <UART_driver.h>

#define FOSC 4915200// Clock Speed
#define BAUD 9600

unsigned char UART_driver_receive_data() {
		/* Wait for data to be received */
		while (!(UCSRA & (1 << RXC)));
		/* Get and return received data from buffer */
		return UDR;
}

void UART_driver_transmit_data() {
    
}


void UART_driver_initialize() {
	UBRRH = (unsigned char)((FOSC / 16 / BAUD - 1) >> 8);
	UBRRL = (unsigned char)(FOSC / 16 / BAUD - 1);
	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}

void main(void)
{
	...
		USART_Init(MYUBRR);
	...
}
void USART_Init(unsigned int ubrr)
{
	