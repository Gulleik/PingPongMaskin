#include "XMEM_driver.h"
#include <stdlib.h>
#include <util/delay.h>

void XMEM_initialize(){
    //Enabling External Memory Interface
    MCUCR |= (1<<SRE);
    //SFIOR |= (1<<XMBK);
    //masking first four bits
    SFIOR |= (1<<XMM2);
}
