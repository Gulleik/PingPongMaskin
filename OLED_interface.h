#ifndef OLED_interface_H
#define OLED_interface_H

#endif

#include <stdlib.h> 
#include <string.h>
  
struct Node { 
    unsigned char menu_ID;
    struct Node* up;
    struct Node* down;
    struct Node* next;
}; 
  
void OLED_menu_initialize();

void OLED_home();