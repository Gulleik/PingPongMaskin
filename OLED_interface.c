#include "OLED_interface.h"
#include "OLED.h"
#include "controller.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>



//const char MenuItem1[] PROGMEM = "Menu1";
//const char MenuItem2[] PROGMEM = "Menu2";
//const char MenuItem3[] PROGMEM = "Menu3";

//char* MenuItemPointers[]  = {MenuItem1, MenuItem2, MenuItem3};

//Home screen
const char HOME0[] = "Home Screen, Option 0"; //First option
const char HOME1[] = "Home Screen, Option 1"; //Second option
const char HOME2[] = "Home Screen, Option 2"; //Third option
const char HOME3[] = "NULL";
const char HOME4[] = "NULL";
const char HOME5[] = "NULL";
const char HOME6[] = "NULL";
const char HOME7[] = "NULL";

//Second screen
const char SECOND0[] = "Second Screen, Option 0"; //First option
const char SECOND1[] = "Second Screen, Option 1"; //Second option
const char SECOND2[] = "Second Screen, Option 2"; //Third option
const char SECOND3[] = "NULL";
const char SECOND4[] = "NULL";
const char SECOND5[] = "NULL";
const char SECOND6[] = "NULL";
const char SECOND_RETURN[] = "Return"; //Return

char* ALTMenuItemPointers[] = {
	HOME0, HOME1, HOME2, HOME3, HOME4, HOME5, HOME6, HOME7,
	SECOND0, SECOND1, SECOND2, SECOND3, SECOND4, SECOND5, SECOND6, SECOND_RETURN};

uint8_t enter() {
	return controller_button_read() == 'j';
}

void traverse_menu(*option) {
	//Traverse up and down on screen
	if (controller_joystick_read_Y() < -95) {
		do {
			*option = (*option + 1) % 8;
		} while (!ALTMenuItemPointers[*options]);
		return 1; //Traversion -> Redraw screen
	}
	else if (controller_joystick_read_Y() > 95) {
		do {
			*option = (*option - 1) % 8;
		} while (!ALTMenuItemPointers[*options]);
		return 1;
	}
	//Traverse in and out of screens
	switch (option) {
		case (HOME0):
			if enter() {
				option = SECOND0;
				return 1; //Traversion -> Redraw screen
			}
			break;
		case (HOME1):
			if enter() {
				//DO SOMETHING
				option = HOME0; //Return to home after function call
				return 1;
			}
			break;
		case (SECOND_RETURN):
			if enter() {
				option = HOME0;
				return 1;
			}
			break;
		default:
			break;
    }
	return 0; //No traversion -> Repeat traversion loop
}


void OLED_menu_interface() {
	//Testing PROGMEM strings
	
  /*
	int i = 0;
	while(1) {
		_delay_ms(2000);
		OLED_reset_position();
		//OLED_print_string((char *)pgm_read_byte(&MenuItemPointers[i]));
		OLED_print_string(ALTMenuItemPointers[i]);
		if (i == 2) i = 0;
		else i++;
	}*/

	//Initialize default option to first option at home screen (HOME0)
	enum menu_options option = HOME0;
	while(1) {
		//Print entire screen
		for (int page = 0; page < 8; page++) {
			OLED_goto_column(0);
			OLED_goto_page(option % 8);
			OLED_print_string(ALTMenuItemPointers[option]);
		}
		//Highlight chosen option
		OLED_invert_page(option % 8);
		//Wait for traversion input
		while (!traverse_menu(&option));
	}
}