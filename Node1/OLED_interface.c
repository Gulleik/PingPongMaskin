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


/*
  .  . .  .  . .  .  . .  .  . . .  . .  .  . .  .  . .  .  . .  .  . .  .  . .  .  . .  .  . .  .  
   .       .       .       .     .  . .  .  . .  .  . .   .       .       .       .       .       . 
     .  .    .  .    .  .    .. ----------------------- .    . .    .  .    .  .    .  .    .  .    
 .       .       .       .    . |                     | .  .     .      .       .       .       .  .
   .  .    .  .    .  .    .  . |                     |. .    .    . .    .  .    .  .    .  .      
  .    .  .    .  .    .  .   . |        HOME         | .   .   .      .   .   .   .   .   .   . .  
    .       .       .       . . |                     |   .   .   .  .   .   .   .   .   .   .     .
  .   . .    .  .    .  .     . |                     |..              .       .       .        .   
    .     .    .  .    .  .  .. ----------------------- .  . .  . . .     . .     . .     . .     . 
  .    .   .       .      .  ../.. .    . | .   . .   \        .         .  .    .       .       . .   
     .   .   .  .   .. ...    /   . . .   |.. .        \  .. . .        .   . .     . .  .     .
  .    .      .    . _--------_    ---------------.  --------------- . .  .         . .         .   
    .     . .    .. /          \   |             | . |             |    .   . .  .     .  .  .   . 
  .   .          . |  PLAY GAME |  |   OPTIONS   |  .|   EXTRAS    | .     .        .     .     .   
    .   . .  .   .  \          /   |             | . |             |   .      . . .   .     . .    .
  .         .  .     '--------'    ---------------   ---------------  .   .  .          . .       .  
     . .  .      .                 /:. .. .      \ . . .. . .  . .    .   .   .  . .      .  .     
  .          .  .          .  .  :/ .       .. .  \ . .      .     .    .   .        .  .      . . 
    .  . . .   .   .   . . ---------------. --------------- .   .  .  .         .  .    .   . .     
  .       .       .       .|             | .|             |      .       .       .       .       . 
  .          .    .  .    .|  CONTROLS   | .|    MOTOR    |             .  .  .   .  .    .      .  
    . .  .      .       . .|             | .|             |  . . .  .     .     .      .    .  .   .
  .       . .      .  .  . ---------------  --------------- .        .  . .   . .    .     .       .  
     . .      . .   .     .          ...     .  . . . .  . .  .  .               .   . .   .  .     
  .      .  .     .    .   .  .   .      . .                 .      .  .  .  . .   .        .   .  .
    .  .      .  .   .   .      .   .        . .  . .  .  .    .  .   .    .         .  . .   .     
  .      . .       .        . .       . .  .     .    .     .    .   .  .     .  .               .  
/**********************************************************************
 * 
 * CONFIGURE MENU
 * 
***********************************************************************/

/*Home*/
//      SCREEN SIZE: "-------------------------."
const char home0[] = "        _-'HOME'-_";
const char home1[] = "Play Game";
const char home2[] = "Options";
const char home3[] = "Extras";
const char home4[] = "";
const char home5[] = "";
const char home6[] = "";
const char home7[] = "";


/*Home -> Options*/
//     SCREEN SIZE: "-------------------------."
const char opt0[] = "      _-'OPTIONS'-_";
const char opt1[] = "Controls";
const char opt2[] = "Motor speed";
const char opt3[] = "";
const char opt4[] = "";
const char opt5[] = "";
const char opt6[] = "";
const char opt_return[] = "Return"; //Return to home screen

/*Home -> Options -> Controls*/
//      SCREEN SIZE: "-------------------------."
const char ctrl0[] = "     _-'CONTROLS'-_";
const char ctrl1[] = "";
const char ctrl2[] = "";
const char ctrl3[] = "";
const char ctrl4[] = "";
const char ctrl5[] = "";
const char ctrl6[] = "";
const char ctrl_return[] = "Return"; //Return to options screen

/*Home -> Options -> Motor*/
//     SCREEN SIZE: "-------------------------."
const char mot0[] = "       _-'MOTOR'-_";
const char mot1[] = "";
const char mot2[] = "";
const char mot3[] = "";
const char mot4[] = "";
const char mot5[] = "";
const char mot6[] = "";
const char mot_return[] = "Return"; //Return to options screen

/*Home -> Extras*/
//      SCREEN SIZE: "-------------------------."
const char ext0[] = "       _-'EXTRAS'-_";
const char ext1[] = "";
const char ext2[] = "";
const char ext3[] = "";
const char ext4[] = "";
const char ext5[] = "";
const char ext6[] = "";
const char ext_return[] = "Return"; //Return to home screen

char* ALTMenuItemPointers[] = {
	home0, home1, home2, home3, home4, home5, home6, home7,
	opt0, opt1, opt2, opt3, opt4, opt5, opt6, opt_return,
	ctrl0, ctrl1, ctrl2, ctrl3, ctrl4, ctrl5, ctrl6, ctrl_return,
	mot0, mot1, mot2, mot3, mot4, mot5, mot6, mot_return,
	ext0, ext1, ext2, ext3, ext4, ext5, ext6, ext_return
};

enum menu_options {
	HOME0, HOME1, HOME2, HOME3, HOME4, HOME5, HOME6, HOME7,
	OPTIONS0, OPTIONS1, OPTIONS2, OPTIONS3, OPTIONS4, OPTIONS5, OPTIONS6, OPTIONS_RETURN,
	CONTROLS0, CONTROLS1, CONTROLS2, CONTROLS3, CONTROLS4, CONTROLS5, CONTROLS6, CONTROLS_RETURN,
	MOTOR0, MOTOR1, MOTOR2, MOTOR3, MOTOR4, MOTOR5, MOTOR6, MOTOR_RETURN,
	EXTRAS0, EXTRAS1, EXTRAS2, EXTRAS3, EXTRAS4, EXTRAS5, EXTRAS6, EXTRAS_RETURN
};

uint8_t enter() {
	return controller_button_read() == 'j';
}

void play_game() {
	OLED_clear();
	OLED_invert_page(2);
	OLED_invert_page(4);
	char c;
	do {
		c = UART_receive();
		controller_CAN_send();
		_delay_ms(100);
	} while (c != 13); // Loop while enter is not pressed
}

uint8_t OLED_FSM(enum menu_options *option) {
	uint8_t screen = *option / 8;
	//Traverse up and down on screen
	char c = UART_receive();
	if (c == 'l'/*controller_joystick_read_Y() < -95*/) { //DOWN
		do {
			*option = screen * 8 + (*option + 1) % 8; // Increment option and loop if out of bounds
		} while (ALTMenuItemPointers[*option][0] == '\0' || *option % 8 == 0); // Skip empty options
		return 1; //Traversion -> Redraw screen
	}
	else if (c == 'o'/*controller_joystick_read_Y() > 95*/) { //UP
		do {
			*option = screen * 8 + (*option - 1) % 8; // Increment option and loop if out of bounds
		} while (ALTMenuItemPointers[*option][0] == '\0' || *option % 8 == 0);  // Skip empty options
		return 1;
	}
	/*FSM*/
	switch (*option) {
		case (HOME1): //Play Game
			if (c == 13/*enter()*/) {
				//RUN PLAY GAME FUNC
				return REDRAW_SCREEN;
			}
			break;
		case (HOME2): //Options
			if (c == 13/*enter()*/) {
				*option = OPTIONS1; // Goto options screen
				return REDRAW_SCREEN;
			}
			break;
		case (HOME3): //Extras
			if (c == 13/*enter()*/) {
				*option = EXTRAS1; //Goto extras screen
				return REDRAW_SCREEN;
			}
			break;
		case (OPTIONS1): //Controls
			if (c == 13/*enter()*/) {
				*option = CONTROLS1; //Goto controls screen
				return REDRAW_SCREEN;
			}
			break;
		case (OPTIONS2): //Motor
			if (c == 13/*enter()*/) {
				*option = MOTOR1; //Goto motor screen
				return REDRAW_SCREEN;
			}
			break;
		case (OPTIONS_RETURN): //Return
			if (c == 13/*enter()*/) {
				*option = HOME1; //Return to home screen
				return REDRAW_SCREEN;
			}
			break;
		case (CONTROLS_RETURN): //Return
			if (c == 13/*enter()*/) {
				*option = OPTIONS1; //Return to options screen
				return REDRAW_SCREEN;
			}
			break;
		case (MOTOR_RETURN): //Return
			if (c == 13/*enter()*/) {
				*option = OPTIONS1; //Return to options screen
				return REDRAW_SCREEN;
			}
			break;
		case (EXTRAS_RETURN): //Return
			if (c == 13/*enter()*/) {
				*option = HOME1; //Return to home screen
				return REDRAW_SCREEN;
			}
			break;
		default:
			break;
    }
	return RETAIN_SCREEN;
}


void OLED_interface() {
	/*Testing PROGMEM strings*/
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
	OLED_clear();
	OLED_reset_position();

	/*Initialize default option to first option at home screen (HOME1)*/
	enum menu_options option = HOME1;
	while(1) {
		printf("option = %d\n\r", option);
		/*Print entire screen*/
		for (int page = 0; page < 8; page++) {
			OLED_goto_column(0);
			OLED_clear_page(page);
			OLED_goto_page(page);
			OLED_print_string(ALTMenuItemPointers[(option / 8) * 8 + page]);
		}
		
		OLED_invert_page(option % 8); //Highlight chosen option
		
		while (!OLED_FSM(&option)); //Run FSM until REDRAW_SCREEN is passed
	}
}