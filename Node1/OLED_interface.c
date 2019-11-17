#define F_CPU 4915200 // clock frequency in Hz

#include "OLED_interface.h"
#include "OLED_refresh.h"
#include "OLED.h"
#include "CAN.h"
#include "controller.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

//const char MenuItem1[] PROGMEM = "Menu1";
//const char MenuItem2[] PROGMEM = "Menu2";
//const char MenuItem3[] PROGMEM = "Menu3";

//char* MenuItemPointers[]  = {MenuItem1, MenuItem2, MenuItem3};


/*
  .  . .  .   . .  .  . .  .  . . .  . .  .  . .  .  . .  .  . .  .  . .  .  . .  .  . . 
   .       .        .       .     .  . .  .  . .  .  . .   .       .       .       .     
 .  .    .  .     .  .   .    .. ----------------------- .    . .    .  .    .  .    .  .
 .       .        .       .    . |                     | .  .     .      .       .       
   .  .    .  .     .  .    .  . |                     |. .    .    . .    .  .    .  .  
  .    .  .    .   .    .  .   . |        HOME         | .   .   .      .   .   .   .   .
    .       .        .       . . |                     |   .   .   .  .   .   .   .   .  
  .   . .    .  .     .  .     . |                     |..              .       .       .
    .      .    .  .    .  .  .. ----------------------- .  . .  . . .     . .     . .   
  .     .   .       .      .  . /   .    . | .   . .   \        .         .  .    .      
 .   .  .     .  .   .. ...    /   . . .   |.. .        \  .. . .        .   . .     . . 
  .    .       .    . _--------_    ---------------.  --------------- . .  .         . . 
    .      . .    .. /          \   |             | . |             |    .   . .  .     .
  .   .           . |  PLAY GAME |  |   OPTIONS   |  .|   EXTRAS    | .     .        .   
    .   . .   .   .  \          /   |             | . |             |   .      . . .    .
  .          .  .     '--------'    ---------------   ---------------  .   .  .          
.    . .  .       .                 /:. .. .      \ . . .. . .  . .    .   .   .  . .   .
  .          .   .          .  .  :/ .       .. .  \ . .      .     .    .   .        .  
    .  . . .    .   .   . . ---------------. --------------- .   .  .  .         .  .    
  .       .        .       .|             | .|             |      .       .       .      
  .          .     .  .    .|  CONTROLS   | .|    MOTOR    |             .  .  .   .  .  
    . .  .      .        . .|             | .|             |  . . .  .     .     .      .
  .       . .       .  .  . ---------------  --------------- .        .  . .   . .    .  
   .       .       .        .     .  . .  .  . .  . | . .   .       .       .       .    
    .  .      .  .    .   .      .   .        . .  .|.  .  .    .  .   .    .         .  
    .  . . .   .   .    . .           ...  . --------------- .   .  .  .         .  .    
  .       .       .        .      .         .|             |      .       .       .      
  .          .    .  .     .  . .     . .   .|   PARAMS    |             .  .  .   .  . .
    . .  .      .       .  .       .        .|             |  . . .  .     .     .      .
  .       . .      .  .  .   . . .   .       --------------- .        .  . .   . .    .  
    .  .      .  .   .   .       .   .        . .  . .  .  .    .  .   .    .         .  
  .      . .       .         . .       . .  .     .    .     .    .   .  .     .  .      
/****************************************************************************************
 * 
 * CONFIGURE MENU
 * 
*****************************************************************************************/

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
const char opt2[] = "Motor";
const char opt3[] = "";
const char opt4[] = "";
const char opt5[] = "";
const char opt6[] = "";
const char opt_return[] = "Return";

/*Home -> Options -> Controls*/
//      SCREEN SIZE: "-------------------------."
const char ctrl0[] = "     _-'CONTROLS'-_";
const char ctrl1[] = "Invert servo";
const char ctrl2[] = "Invert motor";
const char ctrl3[] = "";
const char ctrl4[] = "";
const char ctrl5[] = "";
const char ctrl6[] = "";
const char ctrl_return[] = "Return";

/*Home -> Options -> Motor*/
//     SCREEN SIZE: "-------------------------."
const char mot0[] = "       _-'MOTOR'-_";
const char mot1[] = "Top speed";
const char mot2[] = "Controller parameters";
const char mot3[] = "";
const char mot4[] = "";
const char mot5[] = "";
const char mot6[] = "";
const char mot_return[] = "Return";

/*Home -> Options -> Motor -> Params*/
//     SCREEN SIZE: "-------------------------."
const char par0[] = "    _-'CTRL. PAR.'-_";
const char par1[] = "Kp";
const char par2[] = "Ki";
const char par3[] = "Kd";
const char par4[] = "";
const char par5[] = "";
const char par6[] = "";
const char par_return[] = "Return";

/*Home -> Extras*/
//     SCREEN SIZE: "-------------------------."
const char ext0[] = "       _-'EXTRAS'-_";
const char ext1[] = "Screensaver";
const char ext2[] = "";
const char ext3[] = "";
const char ext4[] = "";
const char ext5[] = "";
const char ext6[] = "";
const char ext_return[] = "Return";

char* menu_string_pointers[] = {
	home0, home1, home2, home3, home4, home5, home6, home7,
	opt0, opt1, opt2, opt3, opt4, opt5, opt6, opt_return,
	ctrl0, ctrl1, ctrl2, ctrl3, ctrl4, ctrl5, ctrl6, ctrl_return,
	mot0, mot1, mot2, mot3, mot4, mot5, mot6, mot_return,
	par0, par1, par2, par3, par4, par5, par6, par_return,
	ext0, ext1, ext2, ext3, ext4, ext5, ext6, ext_return
};

enum menu_options {
	HOME0, HOME1, HOME2, HOME3, HOME4, HOME5, HOME6, HOME7,
	OPTIONS0, OPTIONS1, OPTIONS2, OPTIONS3, OPTIONS4, OPTIONS5, OPTIONS6, OPTIONS_RETURN,
	CONTROLS0, CONTROLS1, CONTROLS2, CONTROLS3, CONTROLS4, CONTROLS5, CONTROLS6, CONTROLS_RETURN,
	MOTOR0, MOTOR1, MOTOR2, MOTOR3, MOTOR4, MOTOR5, MOTOR6, MOTOR_RETURN,
	PARAM0, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5, PARAM6, PARAM_RETURN,
	EXTRAS0, EXTRAS1, EXTRAS2, EXTRAS3, EXTRAS4, EXTRAS5, EXTRAS6, EXTRAS_RETURN
};

/*****************************************************************************************
 * 
*****************************************************************************************/

uint8_t enter_joystick_r() {
	/*Read joystick input and check if over treshold*/
	controller_joystick_read_X();
	return controls_msg.data[0] > 200;
}

uint8_t enter_joystick_l() {
	/*Read joystick input and check if over treshold*/
	controller_joystick_read_X();
	return controls_msg.data[0] < 50;
}

uint8_t enter_joystick_u() {
	/*Read joystick input and check if over treshold*/
	controller_joystick_read_Y();
	return controls_msg.data[1] > 200;
}

uint8_t enter_joystick_d() {
	/*Read joystick input and check if over treshold*/
	controller_joystick_read_Y();
	return controls_msg.data[1] < 50;
}

uint8_t enter_button(enum BUTTON B) {
	/*Check if param button is pressed*/
	controller_button_read();
	return controls_msg.data[4] == B;
}

void play_game() {
	OLED_clear();
	
	/*Show parameters on OLED*/
	/*OLED_goto_page(2);
	OLED_goto_column(0);
	OLED_print_string("Params.: Kp = ");
	char Kp_str[] = "";
	itoa(config_msg.data[1], Kp_str, 10); //Convert int value to str in order to print to OLED
	OLED_print_string(Kp_str);
	OLED_goto_page(3);
	OLED_goto_column(45);
	OLED_print_string("Ki = ");
	char Ki_str[] = "";
	itoa(config_msg.data[2], Ki_str, 10); //Convert int value to str in order to print to OLED
	OLED_print_string(Ki_str);
	OLED_goto_page(4);
	OLED_goto_column(45);
	OLED_print_string("Kd = ");
	char Kd_str[] = "";
	itoa(config_msg.data[3], Kd_str, 10); //Convert int value to str in order to print to OLED
	OLED_print_string(Kd_str);*/

	/*Show quit message on OLED*/
	OLED_goto_page(7);
	OLED_goto_column(10);
	OLED_print_string("HOLD JOYSTICK TO QUIT");

	OLED_update_image();

	/*Loop until joystick is pressed*/
	do {
		/*Send all controller inputs by CAN*/
		controller_CAN_send();
        _delay_ms(50);
	} while (!enter_button(JOYSTICK));
}

void show_slider_selection(uint8_t page) {
	/*Enable screen refresh at specified refresh rate*/
	OLED_refresh_enable();

	/*Loop until joystick is pressed*/
	do {
		/*Read slider input*/
		controller_slider_read_R();

		/*Disable interrupts to prevent screen flickering*/
		cli();
		/*Print Min */
		OLED_clear_page(page);
		OLED_goto_page(page);
		OLED_print_string("Min");

		/*Print slider indicator*/
		OLED_goto_column(controls_msg.data[3]/3 + 20);
		OLED_write_d(0xFF);

		/*Print Max*/
		OLED_goto_column(107);
		OLED_print_string("Max");

		/*Enable interrupts*/
		sei();

		_delay_ms(50);
	} while (!enter_button(JOYSTICK));

	/*Freeze image*/
	OLED_freeze_image();
}

void show_and_increment_value(char name[], uint8_t def, volatile uint8_t *value, uint8_t page) {
	/*Enable screen refresh at specified refresh rate*/
	OLED_refresh_enable();

	/*Loop until joystick is pressed*/
	do {
		OLED_clear_page(page);
		OLED_goto_page(page);

		/*Print param value as string*/
		char val_str[] = "";
		itoa(*value, val_str, 10);

		/*Disable interrupts to prevent screen flickering*/
		cli();

		/*Print param name and increment/decrement operators according to joystick input*/
		OLED_print_string(name);
		if (enter_joystick_l()) {
			*value -= 5;
			OLED_print_string(" - ");
		} else {
			OLED_print_string("   ");
		}
		OLED_print_string(val_str);
		if (enter_joystick_r()) {
			*value += 5;
			OLED_print_string(" +");
		}

		/*Print default value as string*/
		OLED_goto_column(80);
		OLED_print_string("def: ");
		char def_str[] = "";
		itoa(def, def_str, 10);
		OLED_print_string(def_str);

		/*Enable interrupts*/
		sei();
		_delay_ms(50);
	} while (!enter_button(JOYSTICK));

	/*Freeze image*/
	OLED_freeze_image();
}

/*
const char ss0[] = "";
const char ss1[] = "`-:-.   ,-;*`-:-.   ,-;*";
const char ss2[] = "   `=`,'=/     `=`,'=/  ";
const char ss3[] = "     y==/        y==/   ";
const char ss4[] = "   ,=,-<=`.    ,=,-<=`. ";
const char ss5[] = ",-'-'   `-=_,-'-'   `-=_";
const char ss6[] = "";
const char ss7[] = "";

char* ScreenSaver[] = {
	ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7,
};
*/
void OLED_screensaver() {
	OLED_refresh_enable();
	OLED_clear();
	
	uint8_t x_pos = rand() % 128;
	uint8_t y_pos = rand() % 64;

	while(1) {
		cli();
		if (x_pos > 127) {
			x_pos = 0;
		} else if (y_pos > 63) {
			y_pos = 0;
		}
		OLED_set_pixel(x_pos++, y_pos++);
		sei();
		_delay_ms(1);
	}

	OLED_freeze_image();
}

uint8_t OLED_FSM(enum menu_options *option) {
	uint8_t screen = *option / 8;

	/*Traverse up and down on screen*/
	_delay_ms(200);
	if (enter_joystick_d()) {
		/*Loop if option ar header or empty line*/
		do {
			/*Increment option and loop to top if option "below" screen*/
			*option = screen * 8 + (*option + 1) % 8;
		} while (menu_string_pointers[*option][0] == '\0' || *option % 8 == 0);
		return REDRAW_SCREEN;
	}
	else if (enter_joystick_u()) {
		/*Loop if option ar header or empty line*/
		do {
			/*Increment option and loop to bottom if option "above" screen*/
			*option = screen * 8 + (*option - 1) % 8;
		} while (menu_string_pointers[*option][0] == '\0' || *option % 8 == 0);
		return REDRAW_SCREEN;
	}
	
	/*FSM*/
	switch (*option) {
		/*Home: Play Game*/
		case (HOME1):
			if (enter_joystick_r()) {
				/*Set node 2 to RUN state and send by CAN*/
				node2_state_msg.data[0] = 1;
				CAN_write_message(node2_state_msg);

				/*Initiate main play_game function*/
				play_game();

				/*Set node 2 to IDLE state*/
				node2_state_msg.data[0] = 0;
				CAN_write_message(node2_state_msg);
				return REDRAW_SCREEN;
			}
			break;

		/*Home: Options*/
		case (HOME2):
			if (enter_joystick_r()) {
				/*Goto options screen*/
				*option = OPTIONS1;
				return REDRAW_SCREEN;
			}
			break;

		/*Home: Extras*/
		case (HOME3):
			if (enter_joystick_r()) {
				/*Goto extras screen*/
				*option = EXTRAS1;
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options: Controls*/
		case (OPTIONS1):
			if (enter_joystick_r()) {
				/*Goto controls screen*/
				*option = CONTROLS1;
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options: Motor*/
		case (OPTIONS2):
			if (enter_joystick_r()) {
				/*Goto motor screen*/
				*option = MOTOR1;
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options: Return*/
		case (OPTIONS_RETURN):
			if (enter_joystick_r()) {
				/*Return to home screen*/
				*option = HOME2;
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Controls: Invert servo*/
		case (CONTROLS1):
			if (enter_joystick_r()) {
				/*Confure node 2 servo dir and send by CAN*/
				config_msg.data[4] = ~config_msg.data[4];
				CAN_write_message(config_msg);

				/*Print Selection to screen*/
				OLED_goto_page(*option % 8);
				OLED_goto_column(60);
				if (config_msg.data[4]) {
					OLED_print_string_inverted("  True");
				} else {
					OLED_print_string_inverted("  False");
				}
				OLED_update_image();
				_delay_ms(1000);
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Controls: Invert motor*/
		case (CONTROLS2):
			if (enter_joystick_r()) {
				/*Confure node 2 motor dir and send by CAN*/
				config_msg.data[5] = ~config_msg.data[5];
				CAN_write_message(config_msg);

				/*Show selection to screen and let user select*/
				OLED_goto_page(*option % 8);
				OLED_goto_column(60);
				if (config_msg.data[5]) {
					OLED_print_string_inverted("  True");
				} else {
					OLED_print_string_inverted("  False");
				}
				OLED_update_image();
				_delay_ms(1000);
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Controls: Return*/
		case (CONTROLS_RETURN):
			if (enter_joystick_r()) {
				/*Return to options screen*/
				*option = OPTIONS1;
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Motor: Top speed*/
		case (MOTOR1):
			if (enter_joystick_r()) {
				/*Show slider selection and let user select*/
				show_slider_selection(*option % 8);

				/*Configure node 2 top speed and send by CAN*/
				config_msg.data[0] = controls_msg.data[3]; // Configure node 2 top speed
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Motor: Controller params*/
		case (MOTOR2):
			if (enter_joystick_r()) {
				/*Goto params screen*/
				*option = PARAM1;
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Motor: Return*/
		case (MOTOR_RETURN):
			if (enter_joystick_r()) {
				/*Return to options screen*/
				*option = OPTIONS2;
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Motor: Kp*/
		case (PARAM1):
			if (enter_joystick_r() || enter_joystick_l()) {
				/*Show value and let user increment value, configure node 2 and send by CAN*/
				show_and_increment_value("Kp", CONF_DEFAULT_Kp, &config_msg.data[1], *option % 8);
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Motor: Ki*/
		case (PARAM2):
			if (enter_joystick_r() || enter_joystick_l()) {
				/*Show value and let user increment value, configure node 2 and send by CAN*/
				show_and_increment_value("Ki", CONF_DEFAULT_Ki, &config_msg.data[2], *option % 8);
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Motor: Kd*/
		case (PARAM3):
			if (enter_joystick_r() || enter_joystick_l()) {
				/*Show value and let user increment value, configure node 2 and send by CAN*/
				show_and_increment_value("Kd", CONF_DEFAULT_Kd, &config_msg.data[3], *option % 8);
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Options->Motor: Return*/
		case (PARAM_RETURN):
			if (enter_joystick_r()) {
				/*Return to motor screen*/
				*option = MOTOR1; //Return to motor screen
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Extras: Screensaver*/
		case (EXTRAS1):
			if (enter_joystick_r()) {
				/*Show screensaver*/
				OLED_screensaver();
				return REDRAW_SCREEN;
			}
			break;

		/*Home->Extras: Return*/
		case (EXTRAS_RETURN):
			if (enter_joystick_r()) {
				/*Return to home screen*/
				*option = HOME1;
				return REDRAW_SCREEN;
			}
			break;
		default:
			break;
    }
	return RETAIN_SCREEN;
}

void OLED_interface() {
	/*Initialize CAN messages*/
	node2_state_msg.ID = NODE2_STATE;
	node2_state_msg.length = 1;
	config_msg.ID = CONFIG;
	config_msg.length = 6;

	/*Set node 2 to idle state and default configuration*/
	node2_state_msg.data[0] = STATE_IDLE;
	config_msg.data[0] = CONF_DEFAULT_TOP_SPEED;
	config_msg.data[1] = CONF_DEFAULT_Kp;
	config_msg.data[2] = CONF_DEFAULT_Ki;
	config_msg.data[3] = CONF_DEFAULT_Kd;
	config_msg.data[4] = CONF_DEFAULT_INV_SERVO;
	config_msg.data[5] = CONF_DEFAULT_INV_MOTOR;

	/*Send state and configuration to node 2*/
	CAN_write_message(node2_state_msg);
	_delay_ms(1);
	CAN_write_message(config_msg);

	/*Initialize OLED refresh module with refresh rate of 30Hz*/
    OLED_refresh_initialize(60);


	/*Set first option to top of home screen (HOME1)*/
	enum menu_options option = HOME1;
	while(1) {
		/*Print entire screen*/
		for (int page = 0; page < 8; page++) {
			OLED_goto_column(0);
			OLED_clear_page(page);
			OLED_goto_page(page);
			OLED_print_string(menu_string_pointers[(option / 8) * 8 + page]);
		}
		
		/*Highlight chosed option*/
		OLED_invert_page(option % 8);

		OLED_update_image();
		
		/*Run FSM until REDRAW_SCREEN is passed*/
		while (!OLED_FSM(&option));
	}
}