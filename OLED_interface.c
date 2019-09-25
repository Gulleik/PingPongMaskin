#include "OLED_interface.h"

void OLED_menu_initialize() 
{ 
    struct Node* head = NULL; 
    struct Node* second = NULL; 
    struct Node* third = NULL; 
  
    // allocate 3 nodes in the heap 
    head = (struct Node*)malloc(sizeof(struct Node)); 
    second = (struct Node*)malloc(sizeof(struct Node)); 
    third = (struct Node*)malloc(sizeof(struct Node)); 
  
    /* Three blocks have been allocated dynamically.  
     We have pointers to these three blocks as head, 
     second and third      
       head           second           third 
        |                |               | 
        |                |               | 
    +---+-----+     +----+----+     +----+----+ 
    | #  | #  |     | #  | #  |     |  # |  # | 
    +---+-----+     +----+----+     +----+----+ 
     
   # represents any random value. 
   Data is random because we haven’t assigned  
   anything yet  */
  
    head->menu_ID = 0x01; // assign unique ID to first menu node 
    head->down = second; // Link first node with the second node 
    head->up = third; // Link to final node (wrap-around)
    head->next = NULL; // Link to next menu screen (Currently none)
  
    /* data has been assigned to the data part of the first 
     block (block pointed by the head). And next 
     pointer of first block points to second.   
     So they both are linked. 
  
       head          second         third 
        |              |              | 
        |              |              | 
    +---+---+     +----+----+     +-----+----+ 
    | 1  | o----->| #  | #  |     |  #  | #  | 
    +---+---+     +----+----+     +-----+----+     
  */
  
    // assign unique ID to second menu node
    second->menu_ID = 0x02; 
    second->down = third; // Link second node with the third node 
    head->up = head; // Link to first node
    head->next = NULL; // Link to next menu screen (Currently none)
  
    /* data has been assigned to the data part of the second 
     block (block pointed by second). And next 
     pointer of the second block points to the third  
     block. So all three blocks are linked. 
    
       head         second         third 
        |             |             | 
        |             |             | 
    +---+---+     +---+---+     +----+----+ 
    | 1  | o----->| 2 | o-----> |  # |  # | 
    +---+---+     +---+---+     +----+----+      */
  
    third->menu_ID = 0x03; // assign unique menu id to third node
    third->down = head; // Link third node to first node (wrap around)
    third->up = second; // Link third node to second node
    third->next = NULL; // Link to next menu screen (Currently none)
  
    /* data has been assigned to data part of third 
    block (block pointed by third). And next pointer 
    of the third block is made NULL to indicate 
    that the linked list is terminated here. 
  
     We have the linked list ready.   
  
           head     
             | 
             |  
        +---+---+     +---+---+       +----+------+ 
        | 1  | o----->|  2  | o-----> |  3 | NULL | 
        +---+---+     +---+---+       +----+------+        
     
      
    Note that only head is sufficient to represent  
    the whole list.  We can traverse the complete  
    list by following next pointers.    */
  
    return 0; 
}

void OLED_home(){
    

	/*
	// initialize home menu
	OLED_clear();
	OLED_print_string("git pull out");
	OLED_goto_page(1);
	OLED_goto_column(0);
	OLED_print_string("git come");
	OLED_goto_page(2);
	OLED_goto_column(0);
	OLED_print_string("git no baby");

	OLED_goto_page(0);
	OLED_goto_column(0);
	while(1){
		OLED_navigate_ypos_with_joystick(controller_joystick_read_Y(),2);
		if(page == 0){
			OLED_clear_page(page);
			_delay_ms(500);
			OLED_goto_page(0);
			OLED_goto_column(0);
			OLED_print_string("git pull out");
			_delay_ms(500);
		}
		else if(page == 1){
			OLED_clear_page(page);
			_delay_ms(500);
			OLED_goto_page(1);
			OLED_goto_column(0);
			OLED_print_string("git come");
			_delay_ms(500);
		}

		else if(page == 2){
			OLED_clear_page(page);
			_delay_ms(500);
			OLED_goto_page(2);
			OLED_goto_column(0);
			OLED_print_string("git no baby");
			_delay_ms(500);
		}
		
	}*/
	
}
