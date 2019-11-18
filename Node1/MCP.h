#ifndef MCP_H
#define MCP_H

#define MCP_ON 1
#define MCP_OFF 0

#include "SPI.h"
#include "MCP_registers.h"

/**
 * @file
 * @brief MCP driver NODE1
*/

/**
 * @brief Initialize SPI and MCP 
*/
void MCP_initialize();

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


#endif