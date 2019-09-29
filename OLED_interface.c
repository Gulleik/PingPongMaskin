#include "OLED_interface.h"
#include "OLED.h"
#include "controller.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>


/*
const char PROGMEM MenuItem1[] = "Menu1";
const char PROGMEM MenuItem2[] = "Menu2";
const char PROGMEM MenuItem3[] = "Menu3";

char* MenuItemPointers[]  = {MenuItem1, MenuItem2, MenuItem3};
*/

void OLED_menu_interface() {
	//Testing PROGMEM strings
	/*
	int i = 0;
	int current_menu_screen;
	while(1) {
		_delay_ms(2000);
		OLED_reset_position();
		//OLED_print_string(pgm_read_byte(MenuItemPointers[i]));
		OLED_print_string(ALTMenuItemPointers[i]);
		if (i == 2) i = 0;
		else i++;
	}*/

	while(1) {
		unsigned char current_menu_screen = menu_pointer->menu_ID / 8;
		//Print entire menu screen **********UNTESTED**********
		for (int option = 0; option < 8; option++) {
			if (ALTMenuItemPointers[current_menu_screen][option]) {
				OLED_goto_column(0);
				OLED_goto_page(option);
				OLED_print_string(ALTMenuItemPointers[current_menu_screen][option]);
			}
		}

    //Highlight chosen option **********UNTESTED**********
    OLED_invert_page(menu_pointer->menu_ID % 8);
    
    //Menu traversion loop **********UNTESTED**********
    while (1) {
      if (controller_joystick_read_Y < -95) {
        menu_pointer = menu_pointer->down;
        break;
      }
      else if (controller_joystick_read_Y > 95) {
        menu_pointer = menu_pointer->up;
        break;
      }
      else if (controller_button_read() == 'j') {
        menu_pointer = menu_pointer->next;
        break;
      }
    }

    //Break menu loop if option is set to quit menu with next = NULL
    if (!menu_pointer->next) break;
	}
  //Open exit function if available
  switch (menu_pointer->menu_ID) {
    case 0x00: //Menu ID with exit function
      //Do something
      break;
    default:
      //Fancy menu animation
      break;
  }
}


