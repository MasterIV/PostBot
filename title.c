void init_title() {
  printf("press select in\nlevel to program\nrobot\n\n");
  printf("press a in level to run program\n\n");
  printf("press b to abort or return\n\n");
  printf("press start\n");
}

void update_title() {
  //print dat title
  
  //go to level screen when start is pressed
  switch(joypad()) {
	case J_START:
	  set_bkg_data(0, 28, background);
	  init_level();
	  break;
	default:
	  break;
  }
}
