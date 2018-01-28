#include <gb/gb.h>
#include <stdio.h>

// bank 1
void init_title();

// bank 2
void update();
void init_level();

#include "bank2.c"
#include "bank3.c"

void main() {
  SPRITES_8x16;

  VBK_REG = 1;
  VBK_REG = 0;
  
  //SWITCH_ROM_MBC1(3);
  init_title();
  
  //SWITCH_ROM_MBC1(2);
  init_level();

  while(1) {
	update();
	delay(35);
  }
}
