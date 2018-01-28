void init_level() {
  switch(level) {
	case 0:
		bot.direction = 0;
		bot.position.x = 56;
		bot.position.y = 80;
		break;
	case 1:
		bot.direction = 0;
		bot.position.x = 72;
		bot.position.y = 96;
		break;
	case 2:
		bot.direction = 0;
		bot.position.x = 104;
		bot.position.y = 48;
		break;
	case 3:
		bot.direction = 0;
		bot.position.x = 72;
		bot.position.y = 128;
		break;
	case 4:
		bot.direction = 0;
		bot.position.x = 72;
		bot.position.y = 80;
		break;
	case 5:
		bot.direction = 0;
		bot.position.x = 40;
		bot.position.y = 80;
		break;
	case 6:
		bot.direction = 1;
		bot.position.x = 24;
		bot.position.y = 32;
		break;
	case 7:
		bot.direction = 0;
		bot.position.x = 72;
		bot.position.y = 80;
		break;
	default:
		printf("Invalid level");
	
  }
  
  DISPLAY_OFF;
  display_level();
  set_bkg_tiles(0, 0, 20, 18, current_level);
  
  reset_sprites();
  init_bot();
  disable_transmission();
  screen = 1;
  
  DISPLAY_ON;
}

void update_level_running() {
  UBYTE keys, diff;
  
  if(transmission.active)
	update_transmission();
  else
    update_bot();
  
  keys = joypad();
  if(keys != joypad_prev) {
	
	//calculate which key changed
	diff = (joypad_prev ^ keys) & keys;
	joypad_prev = keys;
  
	switch(diff) {
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
}

void update_level_idle() {
  UBYTE keys, diff;
  keys = joypad();
  if(keys != joypad_prev) {
	//calculate which key changed
	diff = (joypad_prev ^ keys) & keys;
	joypad_prev = keys;
  
	switch(diff) {
	  case J_UP: error_sound(); break;
	  case J_DOWN: error_sound(); break;
	  case J_LEFT: error_sound(); break;
	  case J_RIGHT: error_sound(); break;
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
}
