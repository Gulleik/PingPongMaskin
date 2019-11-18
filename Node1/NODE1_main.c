/* NODE!_main.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : Gulleik Olsen, Jostein Lysberg and Armon Hakimi
 */ 

#include "UART.h"
#include "OLED_interface.h"

void XMEM_initialize(){
    //Enabling External Memory Interface
    MCUCR |= (1<<SRE);
    
    //masking first four bits
    SFIOR |= (1<<XMM2);
}

int main(void)
{
    UART_initialize();
    XMEM_initialize();
    OLED_initialize(60); //60Hz refresh rate
    
    OLED_interface();

    while(1);
}

