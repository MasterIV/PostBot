void draw_instructions() {
  
  
  //16 is first arrow tile in 'background.tiles'
  //programming[19] = 16;
  
  //20x18
  unsigned char first_tile_location = 12;
  
  int counter = 0;
  
  for (; counter < 20; counter++) {
	int col = counter % 5;
	int row = counter / 5;
	
	int base_tile = first_tile_location + (program[counter] * 4);
	
    int topleft = ((col * 3) + 63) + (row * 60);
	int topright = topleft + 1;
	int bottomleft = topleft + 20;
	int bottomright = bottomleft + 1;
	
	if (counter >= 10) {
	  topleft += 20;
	  topright += 20;
	  bottomleft += 20;
	  bottomright += 20;
	}
	
	if (counter >= 15) {
	  topleft += 20;
	  topright += 20;
	  bottomleft += 20;
	  bottomright += 20;
	}
	
	if (program[counter] == 0) {
	  programming[topleft] = 0;
	  programming[topright] = 0;
	  programming[bottomleft] = 0;
	  programming[bottomright] = 0;
	} else {
	  programming[topleft] = base_tile;
	  programming[topright] = base_tile + 1;
	  programming[bottomleft] = base_tile + 2;
	  programming[bottomright] = base_tile + 3;
	}
  }
  
  //update background
  set_bkg_tiles(0, 0, 20, 18, programming);
}

void update_programming() {
  if(joypad() == J_B) {
	init_level();
	return;
  }
  
//  if(joypad() == J_SELECT) {
//	  init_level();
//	  return;
//  }
  
  cursor_update();
  
  draw_instructions();
}

void init_programming() {
  screen = 3;
  reset_sprites();
  set_bkg_data(0, 40, background);
  set_bkg_tiles(0, 0, 20, 18, programming);
  
  cursor_init();
}

void set_command(int row, int col) {
  int program_location = (row * 5) + col;
  
  //cycling
  if (program[program_location] == 6)
	program[program_location] = 0;
  else
    program[program_location]++;
}

/*
 0 empty
 1 forward
 2 turnleft
 3 turnright
 4 transmit
 5 function 1
 6 function 2
*/

/*
  0-09 main program
 10-14 function 1
 15-19 function 2
*/
