
#include "ADC.h"

uint8_t ADC_read(uint8_t *channel){
    uint8_t *ext_ADC = (uint8_t *) ADC_BASE_ADDR

    /*Write configuration to MUX-pins, Y-axis to CH1*/
    ext_ADC[0] = channel;
    
    /*Wait for stable digital output*/
    _delay_us(30);
    
    return ext_ADC[0];
}