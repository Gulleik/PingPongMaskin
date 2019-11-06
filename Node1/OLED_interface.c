#define F_CPU 4915200 // clock frequency in Hz

#include "OLED_interface.h"
#include "OLED.h"
#include "CAN_driver.h"
#include "controller.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
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
   .       .       .       .     .  . .  .  . .  . | . .   .       .       .       .       .       . 
    .  .      .  .   .   .      .   .        . .  .|.  .  .    .  .   .    .         .  . .   .     
    .  . . .   .   .   . .           ...  . --------------- .   .  .  .         .  .    .   . .     
  .       .       .       .      .         .|             |      .       .       .       .       . 
  .          .    .  .    .  . .     . .   .|   PARAMS    |             .  .  .   .  .    .      .  
    . .  .      .       . .       .        .|             |  . . .  .     .     .      .    .  .   .
  .       . .      .  .  .  . . .   .       --------------- .        .  . .   . .    .     .       .  
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
const char opt2[] = "Motor";
const char opt3[] = "";
const char opt4[] = "";
const char opt5[] = "";
const char opt6[] = "";
const char opt_return[] = "Return"; //Return to home screen

/*Home -> Options -> Controls*/
//      SCREEN SIZE: "-------------------------."
const char ctrl0[] = "     _-'CONTROLS'-_";
const char ctrl1[] = "Invert servo";
const char ctrl2[] = "Invert motor";
const char ctrl3[] = "";
const char ctrl4[] = "";
const char ctrl5[] = "";
const char ctrl6[] = "";
const char ctrl_return[] = "Return"; //Return to options screen

/*Home -> Options -> Motor*/
//     SCREEN SIZE: "-------------------------."
const char mot0[] = "       _-'MOTOR'-_";
const char mot1[] = "Top speed";
const char mot2[] = "Controller parameters";
const char mot3[] = "";
const char mot4[] = "";
const char mot5[] = "";
const char mot6[] = "";
const char mot_return[] = "Return"; //Return to options screen

/*Home -> Options -> Motor -> Params*/
//     SCREEN SIZE: "-------------------------."
const char par0[] = "    _-'CTRL. PAR.'-_";
const char par1[] = "Kp";
const char par2[] = "Ki";
const char par3[] = "Kd";
const char par4[] = "";
const char par5[] = "";
const char par6[] = "";
const char par_return[] = "Return"; //Return to motor screen

/*Home -> Extras*/
//     SCREEN SIZE: "-------------------------."
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

uint8_t enter_joystick_r() {
	controller_joystick_read_X();
	return controls_msg.data[0] > 200;
}

uint8_t enter_joystick_l() {
	controller_joystick_read_X();
	return controls_msg.data[0] < 50;
}

uint8_t enter_joystick_u() {
	controller_joystick_read_Y();
	return controls_msg.data[1] > 200;
}

uint8_t enter_joystick_d() {
	controller_joystick_read_Y();
	return controls_msg.data[1] < 50;
}

uint8_t enter_button(enum BUTTON B) {
	controller_button_read();
	return controls_msg.data[4] == B;
}

void play_game() {
	OLED_clear();
	
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

	/*OLED_goto_page(7);
	OLED_goto_column(10);
	OLED_print_string("HOLD JOYSTICK TO QUIT");*/

	do {
		controller_CAN_send();
        printf("X: %d, Y: %d, SL: %d, SR: %d, B: %d\n\r", 
			controls_msg.data[0],
			controls_msg.data[1],
			controls_msg.data[2],
			controls_msg.data[3],
			controls_msg.data[4]
        );
        _delay_ms(50);
	} while (!enter_button(JOYSTICK)); // Loop while enter is not pressed
}

void show_slider_selection(uint8_t page) {
	do {
		OLED_clear_page(page);
		OLED_goto_page(page);
		OLED_print_string("Min");
		controller_slider_read_R();
		OLED_goto_column(controls_msg.data[3]/3 + 20);
		OLED_write_d(0xFF);
		OLED_goto_column(107);
		OLED_print_string("Max");
		_delay_ms(50);
	} while (!enter_button(JOYSTICK));
}

void show_and_increment_value(char name[], uint8_t def, volatile uint8_t *value, uint8_t page) {
	do {
		printf("show_and_increment() ran\n\r");
		OLED_clear_page(page);
		OLED_goto_page(page);
		char val_str[] = "";
		char def_str[] = "";
		itoa(*value, val_str, 10); //Convert int value to str in order to print to OLED
		
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
		OLED_goto_column(80);
		OLED_print_string("def: ");
		itoa(def, def_str, 10);
		OLED_print_string(def_str);

		_delay_ms(50);
	} while (!enter_button(JOYSTICK));
}

uint8_t OLED_FSM(enum menu_options *option) {
	uint8_t screen = *option / 8;
	//Traverse up and down on screen
	_delay_ms(200);
	if (enter_joystick_d()) { //DOWN
		do {
			*option = screen * 8 + (*option + 1) % 8; // Increment option and loop if out of bounds
		} while (ALTMenuItemPointers[*option][0] == '\0' || *option % 8 == 0); // Skip empty options and header
		return REDRAW_SCREEN;
	}
	else if (enter_joystick_u()) { //UP
		do {
			*option = screen * 8 + (*option - 1) % 8; // Increment option and loop if out of bounds
		} while (ALTMenuItemPointers[*option][0] == '\0' || *option % 8 == 0);  // Skip empty options and header
		return REDRAW_SCREEN;
	}
	
	/*FSM*/
	switch (*option) {
		case (HOME1): //Play Game
			if (enter_joystick_r()) {
				node2_state_msg.data[0] = 1; // Node 2 Run state
				CAN_write_message(node2_state_msg);
				play_game();
				node2_state_msg.data[0] = 0; // Node 2 Idle state
				CAN_write_message(node2_state_msg);
				return REDRAW_SCREEN;
			}
			break;
		case (HOME2): //Options
			if (enter_joystick_r()) {
				*option = OPTIONS1; // Goto options screen
				return REDRAW_SCREEN;
			}
			break;
		case (HOME3): //Extras
			if (enter_joystick_r()) {
				*option = EXTRAS1; //Goto extras screen
				return REDRAW_SCREEN;
			}
			break;
		case (OPTIONS1): //Controls
			if (enter_joystick_r()) {
				*option = CONTROLS1; //Goto controls screen
				return REDRAW_SCREEN;
			}
			break;
		case (OPTIONS2): //Motor
			if (enter_joystick_r()) {
				*option = MOTOR1; //Goto motor screen
				return REDRAW_SCREEN;
			}
			break;
		case (OPTIONS_RETURN): //Return
			if (enter_joystick_r()) {
				*option = HOME2; //Return to home screen
				return REDRAW_SCREEN;
			}
			break;
		case (CONTROLS1): //Invert servo
			if (enter_joystick_r()) {
				config_msg.data[4] = ~config_msg.data[4]; // Configure node 2 servo dir
				CAN_write_message(config_msg);
				OLED_goto_page(*option % 8);
				OLED_goto_column(60);
				if (config_msg.data[4]) {
					OLED_print_string_inverted("  True");
				} else {
					OLED_print_string_inverted("  False");
				}
				CAN_write_message(config_msg);
				_delay_ms(1000);
				return REDRAW_SCREEN;
			}
			break;
		case (CONTROLS2): //Invert motor
			if (enter_joystick_r()) {
				config_msg.data[5] = ~config_msg.data[5]; // Configure node 2 motor dir
				CAN_write_message(config_msg);
				OLED_goto_page(*option % 8);
				OLED_goto_column(60);
				if (config_msg.data[5]) {
					OLED_print_string_inverted("  True");
				} else {
					OLED_print_string_inverted("  False");
				}
				CAN_write_message(config_msg);
				_delay_ms(1000);
				return REDRAW_SCREEN;
			}
			break;
		case (CONTROLS_RETURN): //Return
			if (enter_joystick_r()) {
				*option = OPTIONS1; //Return to options screen
				return REDRAW_SCREEN;
			}
			break;
		case (MOTOR1): //Top speed
			if (enter_joystick_r()) {
				show_slider_selection(*option % 8);
				config_msg.data[0] = controls_msg.data[3]; // Configure node 2 top speed
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;
		case (MOTOR2): //Controller params
			if (enter_joystick_r()) {
				*option = PARAM1; //Goto params screen
				return REDRAW_SCREEN;
			}
			break;
		case (MOTOR_RETURN): //Return
			if (enter_joystick_r()) {
				*option = OPTIONS2; //Return to options screen
				return REDRAW_SCREEN;
			}
			break;
		case (PARAM1): //Kp
			if (enter_joystick_r() || enter_joystick_l()) {
				show_and_increment_value("Kp", CONF_DEFAULT_Kp, &config_msg.data[1], *option % 8); //Configure node 2 Kp
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;
		case (PARAM2): //Ki
			if (enter_joystick_r() || enter_joystick_l()) {
				show_and_increment_value("Ki", CONF_DEFAULT_Ki, &config_msg.data[2], *option % 8); //Configure node 2 Ki
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;
		case (PARAM3): //Kd
			if (enter_joystick_r() || enter_joystick_l()) {
				show_and_increment_value("Kd", CONF_DEFAULT_Kd, &config_msg.data[3], *option % 8); //COnfigure node 2 Kd
				CAN_write_message(config_msg);
				return REDRAW_SCREEN;
			}
			break;
		case (PARAM_RETURN): //Return
			if (enter_joystick_r()) {
				*option = MOTOR1; //Return to motor screen
				return REDRAW_SCREEN;
			}
			break;
		case (EXTRAS_RETURN): //Return
			if (enter_joystick_r()) {
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
		_delay_msHOME1
		OLED_reseHOME1
		//OLED_prHOME1
		OLED_prinHOME1
		if (i == HOME1
		else i++;HOME1
	}*/
	OLED_clear();
	OLED_reset_position();

	/*Initiate node 2 to idle state and default configuration*/
	node2_state_msg.ID = NODE2_STATE;
	node2_state_msg.length = 1;
	config_msg.ID = CONFIG;
	config_msg.length = 6;

	node2_state_msg.data[0] = 0; //Idle state
	config_msg.data[0] = CONF_DEFAULT_TOP_SPEED; //Default top speed
	config_msg.data[1] = CONF_DEFAULT_Kp; //Default Kp
	config_msg.data[2] = CONF_DEFAULT_Ki; //Default Ki
	config_msg.data[3] = CONF_DEFAULT_Kd; //Default Kd
	config_msg.data[4] = 0; //Default Invert servo
	config_msg.data[5] = 0; //Default Invert motor
	CAN_write_message(node2_state_msg);
	_delay_ms(1);
	CAN_write_message(config_msg);

	printf("CONFIGS: speed = %d, Kp = %d, Ki = %d, Kd = %d, Inv_ser = %d, Inv_mot = %d\n\r",
            config_msg.data[0],
            config_msg.data[1],
            config_msg.data[2],
            config_msg.data[3],
            config_msg.data[4],
            config_msg.data[5],
            config_msg.data[6]
        );

	/*Initialize default option to first option at home screen (HOME1)*/
	enum menu_options option = HOME1;
	while(1) {
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