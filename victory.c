void update_victory() {
  if(joypad() && level < 4) {
	init_level();
  }
}

void init_victory() {
  int i;
  screen = 5;
  level++;
  reset_sprites();
  
  if( level < 4 ) {
	printf("Level completed\n\n");
	printf("Press A to continue\n");
  } else {
	printf("Congratulations!\n\n");
	printf("You completed the game\n");
  }
  
  for(i = 0; i < 20; i++) {
	program[i] = 0;
  }
}
