
#ifndef MCP
#define MCP


void MCP_driver_reset();

void MCP_enable();

void MCP_disable();

uint8_t MCP_read(uint8_t address);

void MCP_write(uint8_t address, uint8_t data);

void MCP_RTS(uint8_t buffer);

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

uint8_t MCP_read_status();

uint8_t mcp_init();