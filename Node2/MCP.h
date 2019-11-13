
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
 * Request to send data on a spesific pin
 * @param buffer; the buffer pin we want to send data on.
*/
void MCP_Request_To_Send(uint8_t buffer);


/**
 * Modify data on a spesific address
 * @param addres; the address to read from.
*/
void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

/**
 * Read status of MCP
*/
uint8_t MCP_read_status();
