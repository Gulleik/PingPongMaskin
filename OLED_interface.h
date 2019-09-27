#ifndef OLED_interface_H
#define OLED_interface_H

#endif

#include <stdlib.h> 
#include <string.h>

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////INITIALIZE MENU////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
struct Node* head = NULL;  
struct Node* second = NULL; 
struct Node* third = NULL; 

struct Node* menu_pointer = head;

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

head->menu_ID = 0x00; // assign unique ID to first menu node 
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
second->menu_ID = 0x01; 
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
|0x0| o----->| 0x1| o-----> |  # |  # | 
+---+---+     +---+---+     +----+----+      */

third->menu_ID = 0x02; // assign unique menu id to third node
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
    |0x0| o----->| 0x1| o----->   |0x2 | NULL | 
    +---+---+     +---+---+       +----+------+        
  
  
Note that only head is sufficient to represent  
the whole list.  We can traverse the complete  cde54es
list by following next pointers.    */

//Home screen
const char AMenu10[] = "Menu0"; //First option
const char AMenu11[] = "Menu1"; //Second option
const char AMenu12[] = "Menu2"; //Third option
const char AMenu13[] = NULL;
const char AMenu14[] = NULL;
const char AMenu15[] = NULL;
const char AMenu16[] = NULL;
const char AMenu17[] = NULL;

//Second screen
const char AMenu20[] = "Menu0"; //First option
const char AMenu21[] = "Menu1"; //Second option
const char AMenu22[] = "Menu2"; //Third option
const char AMenu23[] = NULL;
const char AMenu24[] = NULL;
const char AMenu25[] = NULL;
const char AMenu26[] = NULL;
const char AMenu27[] = "Return"; //Return

char* ALTMenuItemPointers[][] = {
	{AMenu10, AMenu11, AMenu12, AMenu13, AMenu14, AMenu15, AMenu16, AMenu17},
	{AMenu20, AMenu21, AMenu22, AMenu23, AMenu24, AMenu25, AMenu26, AMenu27}
};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
  
struct Node { 
    unsigned char menu_ID;
    struct Node* up;
    struct Node* down;
    struct Node* next;
}; 

void OLED_menu_navigate();

