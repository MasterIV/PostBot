void update_victory() {
	// do something here
  if(joypad()) {
	init_level();
  }
}

void init_victory() {
  screen = 5;
  level++;
  
  printf("Level completed\n\n");
  printf("Press A to continue\n");
}
