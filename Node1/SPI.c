#include "SPI.h"

void SPI_master_initialize(){
    /* Set MOSI and SCK output, all others input */
    DDRB = (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_write_byte(uint8_t data) {
    //Write to SPI data bus
    SPDR = data;
    //Wait for data transfer
    while (!(SPSR & (1<<SPIF)));
}

uint8_t SPI_read_byte() {
    volatile uint8_t data;

    /*Write arbitrary value to SPI*/
    SPDR = 0xFF;

    /*Busy wait for until value received*/
    while(!(SPSR & (1 << SPIF)));

    //Catch returned data
    data = SPDR;
    return data;
}