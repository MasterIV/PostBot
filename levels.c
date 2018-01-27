unsigned int objectives[10];

void init_level() {
  
  switch(level) {
	case 0:
		bot.position.x = 72;
		bot.position.y = 80;
  		set_bkg_tiles(0, 0, 20, 18, level_1);
		break;
	case 1:
		bot.position.x = 72;
		bot.position.y = 80;
  		set_bkg_tiles(0, 0, 20, 18, level_2);
		break;
	default:
		printf("Invalid level");
	
  }
  
  screen = 1;
  reset_sprites();
  init_bot();
  
}

void update_level_running() {
  update_bot();
  
  switch(joypad()) {
	case J_B:
	  init_level();
	  break;
	case J_SELECT:
	  init_programming();
	  break;
	default:
	  break;
  }
  
}

void update_level_idle() {
  switch(joypad()) {
	case J_A:
	  screen = 2;
	  break;
	case J_SELECT:
	  init_programming();
	  break;
	default:
	  break;
  }
}
