#include "title_sprites.tiles"
#include "title.map"

unsigned char instructions;

void init_title() {
  set_bkg_data(0, 138, title_sprites);
  set_bkg_tiles(0, 0, 20, 18, title);
}

void show_instructions() {
  if(instructions) return;
  
  set_bkg_tiles(0, 0, 20, 18, current_level);
  printf(" \n press select in\n level to program\n robot\n\n");
  printf(" press a in level\n to run program\n\n");
  printf(" press b to abort\n or return\n\n");
  printf(" press start\n");
  
  instructions = 1;
}

void update_title() {
  //print dat title
  
  //go to level screen when start is pressed
  if(joypad() == J_START) {
	init_level();
  } else if(joypad()) {
	show_instructions();
  }
}
