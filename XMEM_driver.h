#ifndef XMEM_H
#define XMEM_H

#endif

#include <avr/io.h>


//volatile char *ext_OLED = (char *) 0x1000;
//volatile char *ext_SRAM = (char *) 0x1800;

void XMEM_initialize();

void SRAM_test(void);
