
#ifndef MCP
#define MCP

#define ON 1
#define OFF 0
#endif

void MCP_reset();

uint8_t MCP_read(uint8_t address);

void MCP_write(uint8_t address, uint8_t data);

void MCP_Request_To_Send(uint8_t buffer);

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

uint8_t MCP_read_status();

uint8_t MCP_initialize();