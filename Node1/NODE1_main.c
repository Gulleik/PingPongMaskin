/* NODE!_main.c
 *
 * Created: 28.08.2019 10.45.11
 * Author : Gulleik Olsen, Jostein Lysberg and Armon Hakimi
 */ 

#include "UART.h"
#include "OLED_FSM.h"

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
    OLED_FSM_initialize(60); //Initialize OLED with refresh rate of 60Hz
    
    OLED_FSM_run();
}