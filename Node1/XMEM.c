#include "XMEM.h"
#include <util/delay.h>

void XMEM_initialize(){
    //Enabling External Memory Interface
    MCUCR |= (1<<SRE);
    
    //masking first four bits
    SFIOR |= (1<<XMM2);
}
