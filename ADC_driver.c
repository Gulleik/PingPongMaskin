#include "ADC_driver.h"
#include "XMEM_driver.h"
#include <util/delay.h>



char ADC_read(char *channel){
    volatile char *ext_ADC = (char *) 0x1400;
    
     ext_ADC[0] = channel; //Write configuration to MUX-pins, Y-axis to CH1
    _delay_ms(1);

    return *ext_ADC;
}

