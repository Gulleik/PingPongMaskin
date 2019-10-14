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
const char h0[] = "Goto second screen"; //First option
const char h1[] = "helo"; //Second option
const char h2[] = ""; //Third option
const char h3[] = "Goto first option";
const char h4[] = "";
const char h5[] = "git";
const char h6[] = "no";
const char h7[] = "baby";

//Second screen
const char sec0[] = "helo0"; //First option
const char sec1[] = "helo1"; //Second option
const char sec2[] = "helo2"; //Third option
const char sec3[] = "";
const char sec4[] = "";
const char sec5[] = "";
const char sec6[] = "";
const char sec_return[] = "Return"; //Return

char* ALTMenuItemPointers[] = {
	h0, h1, h2, h3, h4, h5, h6, h7,
	sec0, sec1, sec2, sec3, sec4, sec5, sec6, sec_return};

uint8_t enter() {
	return controller_button_read() == 'j';
}

uint8_t traverse_menu(enum menu_options *option) {
	uint8_t screen = *option / 8;
	//Traverse up and down on screen
	//printf("Up: %d\tDown: %d\tKey press: %d\n\r", controller_joystick_read_Y() < -95, controller_joystick_read_Y() > 95, enter());
	char c = UART_receive();
	if (c == 'l'/*controller_joystick_read_Y() < -95*/) { //DOWN
		do {
			*option = screen * 8 + (*option + 1) % 8; // Increment option and loop if out of bounds
		} while (ALTMenuItemPointers[*option][0] == '\0');
		return 1; //Traversion -> Redraw screen
	}
	else if (c == 'o'/*controller_joystick_read_Y() > 95*/) { //UP
		do {
			*option = screen * 8 + (*option - 1) % 8;
		} while (ALTMenuItemPointers[*option][0] == '\0'); // Increment option and loop if out of bounds
		return 1;
	}
	//Traverse in and out of screens
	switch (*option) {
		case (HOME0):
			if (c == 13/*enter()*/) {
				*option = SECOND0;
				return 1; //Traversion -> Redraw screen
			}
			break;
		case (HOME3):
			if (c == 13/*enter()*/) {
				//DO SOMETHING
				*option = HOME0; //Return to home after function call
				return 1;
			}
			break;
		case (SECOND_RETURN):
			if (c == 13/*enter()*/) {
				*option = HOME0;
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
		printf("option = %d\n\r", option);
		//Print entire screen
		for (int page = 0; page < 8; page++) {
			OLED_goto_column(0);
			OLED_clear_page(page);
			OLED_goto_page(page);
			OLED_print_string(ALTMenuItemPointers[(option / 8) * 8 + page]);
		}
		//Highlight chosen option
		OLED_invert_page(option % 8);
		//Wait for traversion input
		while (!traverse_menu(&option));
	}
}