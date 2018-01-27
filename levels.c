void init_level() {
  
  switch(level) {
	case 0:
		bot.position.x = 72;
		bot.position.y = 80;
		copy_map(current_level, level_1);
		break;
	case 1:
		bot.position.x = 72;
		bot.position.y = 80;
		copy_map(current_level, level_2);
		break;
	default:
		printf("Invalid level");
	
  }
  
  set_bkg_data(0, 28, levelset);
  set_bkg_tiles(0, 0, 20, 18, current_level);
  
  reset_sprites();
  init_bot();
  disable_transmission();
  screen = 1;
  
}

void update_level_running() {
  if(transmission.active)
	update_transmission();
  else
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
