#include "SPI_communication_driver.h"
#include "MCP_driver.h"
#include <avr/io.h>



void MCP_driver_reset(){
    PORTB = 0<<PB4;
    SPI_write_byte(RESET);
    PORTB = 1<<PB4;
}

uint8_t MCP_read(uint8_t address) {
    PORTB = 0<<PB4;
    SPI_write_byte(READ);
    SPI_write_byte(address);

    uint8_t data = SPI_read_byte();
    PORTB = 1<<PB4;
    return data;
}

void MCP_write(uint8_t address, uint8_t data){
    PORTB = 0<<PB4;
    SPI_write_byte(WRITE);
    SPI_write_byte(address);
    SPI_write_byte(data);
    PORTB = 1<<PB4;
}

void MCP_RTS(){
    PORTB = 0<<PB4;
    SPI_write_byte(RTS);
    PORTB = 1<<PB4;
}

void MCP_read_status(){
    PORTB = 0<<PB4;
    SPI_write_byte(READ_STATUS);
    uint8_t data = SPI_read_byte();
    PORTB = 1<<PB4;
    return data;
}

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
    PORTB = 0<<PB4;
    SPI_write_byte(BIT_MODIFY);
    SPI_write_byte(mask);
    SPI_write_byte(address);     
}