#include "OLED_interface.h"
//#include "OLED.h"
#include "controller.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>



//const char MenuItem1[] PROGMEM = "Menu1";
//const char MenuItem2[] PROGMEM = "Menu2";
//const char MenuItem3[] PROGMEM = "Menu3";

//char* MenuItemPointers[]  = {MenuItem1, MenuItem2, MenuItem3};

//Home screen
const char AMenu10[] = "Home Screen, Option 1"; //First option
const char AMenu11[] = "Home Screen, Option 2"; //Second option
const char AMenu12[] = "Home Screen, Option 3"; //Third option
//const char AMenu13[] = NULL;
//const char AMenu14[] = NULL;
//const char AMenu15[] = NULL;
//const char AMenu16[] = NULL;
//const char AMenu17[] = NULL;

//Second screen
//const char AMenu20[] = "Second Screen, Option 1"; //First option
//const char AMenu21[] = "Second Screen, Option 2"; //Second option
//const char AMenu22[] = "Second Screen, Option 3"; //Third option
//const char AMenu23[] = NULL;
//const char AMenu24[] = NULL;
//const char AMenu25[] = NULL;
//const char AMenu26[] = NULL;
//const char AMenu27[] = "Return"; //Return

char* ALTMenuItemPointers[] = {AMenu10, AMenu11, AMenu12};

void OLED_menu_interface() {
	//Testing PROGMEM strings
	
	int i = 0;
	int current_menu_screen;/*
	while(1) {
		_delay_ms(2000);
		OLED_reset_position();
		//OLED_print_string((char *)pgm_read_byte(&MenuItemPointers[i]));
		OLED_print_string(ALTMenuItemPointers[i]);
		if (i == 2) i = 0;
		else i++;
	}*/
  /*
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
  }*/
}


