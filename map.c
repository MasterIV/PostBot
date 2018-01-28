const unsigned char tile_objective_inactive = 17;
const unsigned char tile_objective_active = 21;

int get_offset(struct Vector *pos) {
  unsigned char x, y;
  x = pos->x / 8 - 1;
  y = pos->y / 8 - 2;
  return x + y * 20;
}

unsigned char tile_at(struct Vector *pos) {
  int offset = get_offset(pos);
  
  if(offset < 360 && offset > 0)
    return current_level[offset];
  else 
	return 0;
}

unsigned char tile_at_next(struct Vector *pos, struct Vector *velocity) {
  struct Vector dest;
  dest.x = pos->x + velocity->x * 7;
  dest.y = pos->y + velocity->y * 7;
  return tile_at(&dest);
}


void set_velocity(unsigned char direction, struct Vector *velocity) {
  switch(direction) {
	case 0: // up
	  velocity->x = 0;
	  velocity->y = -1;
	  break;
	case 1: // right
	  velocity->x = 1;
	  velocity->y = 0;
	  break;
	case 2: // down
	  velocity->x = 0;
	  velocity->y = 1;
	  break;
	case 3: // left
	  velocity->x = -1;
	  velocity->y = 0;
	  break;
  }
}

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
	display_victory();
  } else {
	printf("Congratulations!\n\n");
	printf("You completed the game\n");
  }
  
  for(i = 0; i < 20; i++)
	program[i] = 0;
  
  waitpad(255);
  init_level();
}

void toggle_objective(struct Vector *pos) {
  int offset = get_offset(pos);
  
  current_level[offset] = tile_objective_active;
  current_level[offset+1] = tile_objective_active+1;
  current_level[offset+20] = tile_objective_active+2;
  current_level[offset+21] = tile_objective_active+3;
  set_bkg_tiles(0, 0, 20, 18, current_level);
  
  objectives--;
  if(objectives < 1)
	init_victory();
}
