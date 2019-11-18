#include "MCP.h"

void MCP_enable(uint8_t state){
    if(state){
        PORTB = 0<<PB4;
    }else{    
        PORTB = 0b00000001<<PB4;
    }
}

void MCP_reset(){
    MCP_enable(MCP_ON);
    SPI_write_byte(MCP_RESET);
    MCP_enable(MCP_OFF);
}

void MCP_initialize() {
    SPI_master_initialize();
    MCP_reset();
}

uint8_t MCP_read(uint8_t address) {
    MCP_enable(MCP_ON);
    SPI_write_byte(MCP_READ);
    SPI_write_byte(address);
    uint8_t data = SPI_read_byte();
    MCP_enable(MCP_OFF);
    return data;
}

void MCP_write(uint8_t address, uint8_t data){
    MCP_enable(MCP_ON);
    SPI_write_byte(MCP_WRITE);
    SPI_write_byte(address);
    SPI_write_byte(data);
    MCP_enable(MCP_OFF);
}

void MCP_Request_To_Send(uint8_t buffer){
    MCP_enable(MCP_ON);
    switch (buffer) {
        case 0x00:
            SPI_write_byte(MCP_RTS_TX0);
            break;
        case 0x01:
            SPI_write_byte(MCP_RTS_TX1);
            break;
        case 0x02:
            SPI_write_byte(MCP_RTS_TX2);
            break;
    }
    SPI_write_byte(MCP_RTS_TX0);
    MCP_enable(MCP_OFF);
}

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
    
    MCP_enable(MCP_ON);
    SPI_write_byte(MCP_BITMOD);
    SPI_write_byte(address);     
    SPI_write_byte(mask);     
    SPI_write_byte(data);
    MCP_enable(MCP_OFF);
    
}

