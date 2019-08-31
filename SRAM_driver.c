#include "SRAM_driver.h"
#include <stdlib.h>
#include <util/delay.h>

void SRAM_driver_initialize(){
    

    /*Enabeling External Memory Interface*/
    MCUCR |= (1<<SRE);
    //SFIOR |= (1<<XMBK);
    SFIOR |= (1<<XMM2);
}
/*
void SRAM_test(void){
    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size= 0x800;
    uint16_t write_errors= 0;
    uint16_t retrieval_errors= 0;
    printf("Starting SRAM test...\n");// rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);write_errors++;
        }
    }
    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed);// reset the PRNG to the stateit had before the write phase
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}
*/

void SRAM_driver_write(unsigned int uiAddress, unsigned char ucData){
    ///* Wait for completion of previous write */
    while(EECR & (1<<EEWE));
    
    /*Ready AVR to write*/
    PORTD = (1 << PD6);
    /*setting ALE high*/
    PORTE = (1 << PE1);

    PORTC = 0x00;
    PORTA = 0x00;
    //PORTA = uiAddress; //AD7:0 
    //PORTC = (uiAddress >> 8); //A15:8
    /* Set ALE low*/
    PORTE = (0 << PE1);

    _delay_ms(100);

    PORTA = ucData; //AD7:0
}

unsigned char SRAM_driver_read(unsigned int uiAddress){
    /* Wait for completion of previous write */
    
    while(EECR & (1<<EEWE));
    
    /* Set up address register */
    EEAR = uiAddress;
    
    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);
    
    /* Return data from data register */
    return EEDR;
}