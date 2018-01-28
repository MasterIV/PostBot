#include <gb/gb.h>
#include <stdio.h>

#include "title_sprites.tiles"
#include "title.map"
#include "sprites.tiles"

void init_title() {
  int i;
  
  set_sprite_data(0, 68, sprites);
  set_bkg_data(0, 138, title_sprites);
  set_bkg_tiles(0, 0, 20, 18, title);
  
  SHOW_SPRITES;  
  SHOW_BKG;
  DISPLAY_ON;
  
  waitpad(255);
  
  for(i =0; i < 360; i++)
	title[i] = 0;
  
  set_bkg_tiles(0, 0, 20, 18, title);
  printf(" \n press select in\n level to program\n robot\n\n");
  printf(" press a in level\n to run program\n\n");
  printf(" press b to abort\n or return\n\n");
  printf(" press start\n");
  
  waitpad(255);
}
