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

enum menu_options {
	HOME0, HOME1, HOME2, HOME3, HOME4, HOME5, HOME6, HOME7,
	SECOND0, SECOND1, SECOND2, SECOND3, SECOND4, SECOND5, SECOND6, SECOND_RETURN
};

void OLED_menu_interface();

