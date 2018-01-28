#include <gb/gb.h>

#include "background.tiles"
#include "programming.map"

void show_programming(unsigned char *dest) {
  int i;
  
  set_bkg_data(0, 40, background);
  set_bkg_tiles(0, 0, 20, 18, programming);
  
  for(i = 0; i < 360; i++) 
	dest[i] = programming[i];
}
