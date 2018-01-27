struct Vector {
  int x;
  int y;
};

struct Bot {
  struct Vector position; 
  struct Vector velocity;
  
  unsigned char direction;
  unsigned char command;
  unsigned char animation;
  unsigned char delay;
} bot;

unsigned char func_1_return;
unsigned char func_2_return;

void turn_bot() {
  if(bot.direction % 2) {
	// horizontal sprites
	set_sprite_tile(0, 8);
	set_sprite_tile(1, 10);
  } else {
	// vertical sprites
	set_sprite_tile(0, 4);
	set_sprite_tile(1, 6);
  }
	
  if(bot.direction > 1) {
	set_sprite_prop(0, S_FLIPY);
	set_sprite_prop(1, S_FLIPY);
  }
}

void move_bot() {
  move_sprite(0, bot.position.x, bot.position.y);
  move_sprite(1, bot.position.x+8, bot.position.y);
}

void init_bot() {
  program[0] = 1;
  program[1] = 3;
  program[2] = 1;
  program[3] = 1;
  
  bot.command = 0;
  bot.direction = 0;  
  bot.animation = 0; 
  bot.delay = 0;
  
  turn_bot();
  move_bot();
}

void command_move() {
  switch(bot.direction) {
	case 0: // up
	  bot.velocity.x = 0;
	  bot.velocity.y = -1;
	  break;
	case 1: // right
	  bot.velocity.x = 1;
	  bot.velocity.y = 0;
	  break;
	case 2: // down
	  bot.velocity.x = 0;
	  bot.velocity.y = 1;
	  break;
	case 3: // left
	  bot.velocity.x = -1;
	  bot.velocity.y = 0;
	  break;
  }
  
  bot.animation = 16;
}

void command_turn(char dir) {
  if(dir < 0 && bot.direction == 0)
	bot.direction = 3;
  else if(dir > 0 && bot.direction == 3)
	bot.direction = 0;
  else
	bot.direction = bot.direction + dir;
	
  turn_bot();
  bot.delay = 5;
}

unsigned char command_next(unsigned char current) {
  current = current + 1;  
  
  switch(current) {
	case 10: // end of main program	
	  return 42;
	case 15: // end of function 1
	  return func_1_return;
	case 20: // end of function 2
	  return func_2_return;
	default:
	  return current;
  }
}


void update_bot() {
  if(bot.delay > 0) {
	bot.delay--;
  } else if(bot.animation > 0) {
	bot.animation--;
	bot.position.x = bot.position.x + bot.velocity.x;
	bot.position.y = bot.position.y + bot.velocity.y;
  	move_bot();
	
	if(bot.animation < 1) 
	  bot.delay = 5;
  } else if(bot.command < 20) {
	switch(program[bot.command]) {
	  case 1: // Move forward
	  	command_move();
	  	break;
	  case 2: // Turn Left
	  	command_turn(-1);
	  	break;
	  case 3: // Turn Right
	  	command_turn(1);
	  	break;
	  case 4: // Transmit
	  
	  	break;
	  case 5: // Function 1
	    func_1_return = command_next(bot.command);
	    bot.command = 10;
	  	return;
	  case 6: // Function 2
	    func_2_return = command_next(bot.command);
	    bot.command = 15;
	  	return;
	}
	
	bot.command = command_next(bot.command);
  }
}

