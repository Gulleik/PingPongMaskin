
#ifndef MCP
#define MCP


#define ON 1
#define OFF 0

/**
 * @brief Initialize SPI and MCP 
*/
void MCP_initialize();

/**
 *  @brief Resets MCP 
*/
void MCP_reset();

/**
 *  @brief Reads data from the AVR
 * @param address; The adress that is to be read from
*/
uint8_t MCP_read(uint8_t address);

/**
 *  @brief Write data to a spesific address on the AVR
 * @param address; The adress that is to be written to
 * @param data; Data that is to be written
*/
void MCP_write(uint8_t address, uint8_t data);

/**
 * @brief Request to send data on a spesific pin
 * @param buffer; The buffer pin we want to send data on.
*/
void MCP_Request_To_Send(uint8_t buffer);


/**
 * @brief Modify data on a spesific address
 * @param addres; The address to read from.
*/
void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

/**
 * @brief Read status of MCP
*/
uint8_t MCP_read_status();

#endif