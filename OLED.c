
#include "OLED.h"
#include "fonts.h"
#include "string.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

static unsigned int position = 0;

void OLED_write_c(char c) {
  volatile char *ext_OLED = (char *) 0x1000;
  ext_OLED[0] = c;
}

void OLED_write_d(unsigned char data) {
  volatile char *ext_OLED = (char *) 0x1200;

  ext_OLED = data;
}

void OLED_write_char(char* c) {
  volatile char *ext_OLED = (char *) 0x1200;

  for (int segment = 0; segment < 5; segment += 1) {
    ext_OLED[0]= pgm_read_byte(&(font5[c[0]-32][segment]));;
  }
}

void OLED_initialize(){
  OLED_write_c(0xae);        //  display  off        
  OLED_write_c(0xa1);        //segment  remap        
  //OLED_write_c(0xda);        //common  pads  hardware:  alternative        
  OLED_write_c(0x12);        
  OLED_write_c(0xc8);        //common  output scan direction:com63~com0       
  OLED_write_c(0xa8);        //multiplex  ration  mode:63        
  OLED_write_c(0x3f);        
  OLED_write_c(0xd5);        //display  divide ratio/osc. freq. mode       
  OLED_write_c(0x80);                
  OLED_write_c(0x81);        //contrast  control          
  OLED_write_c(0x50);           //contrast level [0x00-0xFF]      
  OLED_write_c(0xd9);        //set  pre-charge  period                        
  OLED_write_c(0x20);        //Set  Memory  Addressing  Mode        
  OLED_write_c(0x02);                
  OLED_write_c(0xdb);        //VCOM  deselect  level  mode        
  OLED_write_c(0x30);                
  OLED_write_c(0xad);        //master  configuration          
  OLED_write_c(0x00);                
  OLED_write_c(0xa4);        //out  follows  RAM  content        
  OLED_write_c(0xa6);        //set  normal  display        
  OLED_write_c(0xaf);        //  display  on 
} 

void OLED_goto_line(char page){
   char p = 0xB0 + page;
   OLED_write_c(p);
}

void OLED_print(char* text){
  int length = strlen(text);
  printf("length=%d", length);
  for(int i = 0; i<length;i++){
    OLED_write_d(text[i]);
  }
}

void OLED_goto_column(char column){
  OLED_write_c(0x21);
  OLED_write_c(0x0);
  OLED_write_c(0xEF);
}

void OLED_reset(){
  volatile char *ext_OLED = (char *) 0x1200;
  for (int i = 0; i<8; i++){
    OLED_goto_line(i);
    for (int f = 0; f<128;f++){
      ext_OLED[0] = 0;
    }
  }
}

OLED_clear_line(int line){
  OLED_goto_line(line);
    for (int f = 0; f<128;f++){
      OLED_goto_column(f);
      OLED_write_d(0);
    }
}