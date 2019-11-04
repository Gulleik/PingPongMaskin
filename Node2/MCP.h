
#ifndef MCP
#define MCP
#endif

#define ON 1
#define OFF 0

/**
 * Initialize SPI and MCP 
*/
void MCP_initialize();

/**
 * Resets MCP 
*/
void MCP_reset();


/**
 * Reads data from the AVR
 * @param address; the adress that is to be read from
*/
uint8_t MCP_read(uint8_t address);

/**
 * write data to a spesific address on the AVR
 * @param address; the adress that is to be written to
 * @param data; data that is to be written
*/
void MCP_write(uint8_t address, uint8_t data);

/**
 * Reads data from the AVR
 * @param buffer; the adress that is to be read from
*/
void MCP_Request_To_Send(uint8_t buffer);

void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

uint8_t MCP_read_status();
