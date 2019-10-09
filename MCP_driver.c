#include "SPI_communication_driver.h"
#include "MCP_driver.h"
#include <avr/io.h>


void MCP_enable(){
    PORTB = 0<<PB4;
}

void MCP_disable() {
    PORTB = 1<<PB4;
}

void MCP_driver_reset(){
    MCP_enable();
    SPI_write_byte(MCP_RESET);
    MCP_disable();
}

uint8_t MCP_read(uint8_t address) {
    MCP_enable();
    SPI_write_byte(MCP_READ);
    SPI_write_byte(address);

    uint8_t data = SPI_read_byte();
    MCP_disable();
    return data;
}

void MCP_write(uint8_t address, uint8_t data){
    MCP_enable();
    SPI_write_byte(MCP_WRITE);
    SPI_write_byte(address);
    SPI_write_byte(data);
    MCP_disable();
}

void MCP_RTS(){
    MCP_enable();
    SPI_write_byte(MCP_RTS_TX0);
    MCP_disable();
}

void MCP_read_status(){
    MCP_enable();
    SPI_write_byte(MCP_READ_STATUS);
    uint8_t data = SPI_read_byte();
    MCP_disable();
    return data;
}

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
    
    MCP_enable();
    SPI_write_byte(MCP_BITMOD);
    SPI_write_byte(address);     
    SPI_write_byte(mask);     
    SPI_write_byte(data);
    MCP_disable();
    
}

