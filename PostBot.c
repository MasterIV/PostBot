#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <rand.h>

#include "background.tiles"
#include "sprites.tiles"
#include "command.map"
#include "level_1.map"
#include "level_2.map"
#include "programming.map"
#include "title.map"

/*
  0-09 main program
 10-14 function 1
 15-19 function 2
*/
char program[20];

/*
 0 = title screen
 1 = level, program not running
 2 = level, program running
 3 = programming
 4 = command selection
 5 = level completed
*/
int screen;

// current level
char level;

/** move all sprites out of the screen */
void reset_sprites() {
  int i;
  for(i = 0; i < 40; i++)
	move_sprite(i, 0, 0);
}

void init_programming();
void init_level();

#include "bot.c"
#include "command.c"
#include "cursor.c"
#include "levels.c"
#include "programming.c"
#include "title.c"
#include "victory.c"

void init() {
  //init_programming();
  //init_level();
  init_title();
}

void update() {
  switch(screen) {
	case 0:
		update_title();
		break;
	case 1:
		update_level_idle();
		break;
	case 2:
		update_level_running();
		break;
	case 3:
		update_programming();
		break;
	case 4:
		update_command_selection();
		break;
	case 5:
		update_victory();
		break;
  }
}

void main() {
  
  SPRITES_8x16;

  set_sprite_data(0, 12, sprites);

  VBK_REG = 1;
  VBK_REG = 0;

  //set_bkg_tiles(0, 0, 17, 30, lanes);
  
  init();

  SHOW_SPRITES;  
  SHOW_BKG;
  DISPLAY_ON;

  while(1) {
	update();
	delay(35);
  }
}
