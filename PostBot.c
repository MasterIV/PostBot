#include <gb/gb.h>
#include <stdio.h>

struct Vector {
  int x;
  int y;
};

void init_programming();
void init_level();
void init_victory();
void set_command(int row, int col);

/* 0-09 main program
  10-14 function 1
  15-19 function 2 */
UBYTE program[20];

/* 0 = title screen
   1 = level, program not running
   2 = level, program running
   3 = programming
   4 = command selection
   5 = level completed */
int screen;

// current level
int objectives;
UBYTE level;
UBYTE current_level[360];

// bank 1: title screen
void show_title();
void display_title() {
  SWITCH_ROM_MBC1(1);
  show_title();
}

// bank 2: levels
int show_level(unsigned char level, unsigned char *dest);
void display_level() {
  SWITCH_ROM_MBC1(2);
  objectives = show_level(level, &current_level);
}

// bank 3: programming
void show_programming(unsigned char *dest);
void display_programming() {
  SWITCH_ROM_MBC1(3);
  show_programming(&current_level);
}

// bank 4: victory
void show_victory();
void display_victory() {
  SWITCH_ROM_MBC1(1);
  show_victory();
}


/** move all sprites out of the screen */
void reset_sprites() {
  int i;
  for(i = 0; i < 40; i++) {
	move_sprite(i, 0, 0);
	set_sprite_prop(i, 0);
  }
}

#include "sounds.c"
#include "map.c"
#include "transmission.c"
#include "bot.c"
#include "cursor.c"
#include "levels.c"
#include "programming.c"

void update() {
  switch(screen) {
	case 1:
		update_level_idle();
		break;
	case 2:
		update_level_running();
		break;
	case 3:
		update_programming();
		break;
	case 5:
		update_victory();
		break;
  }
}

void main() {
  SPRITES_8x16;

  VBK_REG = 1;
  VBK_REG = 0;
  
  display_title();
  
  SHOW_SPRITES;  
  SHOW_BKG;
  DISPLAY_ON;
  
  waitpad(255);
  
  set_bkg_tiles(0, 0, 20, 18, current_level);
  
  printf(" \n press select in\n level to program\n robot\n\n");
  printf(" press a in level\n to run program\n\n");
  printf(" press b to abort\n or return\n\n");
  printf(" press start\n");
  
  waitpad(J_START);
  
  SWITCH_ROM_MBC1(2);
  init_level();

  while(1) {
	update();
	delay(35);
  }
}
