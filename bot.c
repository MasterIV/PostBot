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

const unsigned char bot_sprit_up = 24;
const unsigned char bot_sprit_down = 4;
const unsigned char bot_sprit_side = 44;

void turn_bot() {
  unsigned char ani_offset = 0;
  
  if(bot.animation > 0) {
	ani_offset = 1+(bot.animation/4)*4;
  }
  
  if(bot.direction == 3) {
	// right sprites
	set_sprite_tile(0, ani_offset+bot_sprit_side+2);
	set_sprite_tile(1, ani_offset+bot_sprit_side);
  } else if(bot.direction == 1) {
	// left sprites
	set_sprite_tile(0, ani_offset+bot_sprit_side);
	set_sprite_tile(1, ani_offset+bot_sprit_side+2);
  } else if(bot.direction == 2) {
	// down sprites
	set_sprite_tile(0, ani_offset+bot_sprit_down);
	set_sprite_tile(1, ani_offset+bot_sprit_down+2);
  } else {
	// up sprites
	set_sprite_tile(0, ani_offset+bot_sprit_up);
	set_sprite_tile(1, ani_offset+bot_sprit_up+2);
  }
	
  if(bot.direction == 3) {
	set_sprite_prop(0, S_FLIPX);
	set_sprite_prop(1, S_FLIPX);
  } else {
	set_sprite_prop(0, 0);
	set_sprite_prop(1, 0);
  }
}

void move_bot() {
  move_sprite(0, bot.position.x, bot.position.y);
  move_sprite(1, bot.position.x+8, bot.position.y);
}

void init_bot() {
  bot.command = 0;
  bot.animation = 0; 
  bot.delay = 0;
  
  turn_bot();
  move_bot();
}

void command_move() {
  set_velocity(bot.direction, &bot.velocity);
  
  walk_sound();
  
  if(tile_at_next(&bot.position, &bot.velocity, 16) < tile_objective_inactive)
  	bot.animation = 16;
  else
	bot.delay = 10;
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
	turn_bot();
	
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
	    init_transmission(bot.direction, &bot.position);
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

