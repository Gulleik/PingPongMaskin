
#ifndef MCP
#define MCP

#define RESET 11000000
#define READ 00000011
#define WRITE 00000011
#define READ_STATUS 10100000
#define BIT_MODIFY 00000101
#define RTS 10000001
#endif

void MCP_driver_reset();

uint8_t MCP_read(uint8_t address);

void MCP_write(uint8_t address, uint8_t data);

void MCP_RTS();

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);