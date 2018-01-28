#include <gb/gb.h>

#include "title_sprites.tiles"
#include "title.map"
#include "sprites.tiles"
#include "victory_sprites.tiles"
#include "victory.map"

void show_victory() {
  set_bkg_data(0, 63, victory_sprites);
  set_bkg_tiles(0, 0, 20, 18, victory);
}

void show_title() {
  set_sprite_data(0, 68, sprites);
  set_bkg_data(0, 138, title_sprites);
  set_bkg_tiles(0, 0, 20, 18, title);
}
