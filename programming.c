void update_programming() {
  
  if(joypad() == J_B)
	init_level();
  
	// do something here
}

void init_programming() {
  screen = 3;
  reset_sprites();
  set_bkg_tiles(0, 0, 20, 18, programming);
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
