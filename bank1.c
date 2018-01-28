#include <gb/gb.h>

#include "title_sprites.tiles"
#include "title.map"
#include "sprites.tiles"
#include "victory_sprites.tiles"
#include "victory.map"

void show_victory(unsigned char *dest) {
  int i;
  
  set_bkg_data(0, 83, victory_sprites);
  set_bkg_tiles(0, 0, 20, 18, victory);
  
  for(i = 0; i < 360; i++) 
	dest[i] = victory[i];
}

void show_title() {
  set_sprite_data(0, 68, sprites);
  set_bkg_data(0, 140, title_sprites);
  set_bkg_tiles(0, 0, 20, 18, title);
}
