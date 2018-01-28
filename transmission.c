struct Transmission {
  unsigned char active;
  unsigned char animation;
  struct Vector position; 
  struct Vector velocity;
} transmission;


void move_transmission() {
  move_sprite(2, transmission.position.x, transmission.position.y);
  move_sprite(3, transmission.position.x+8, transmission.position.y);
}

void disable_transmission() {
  transmission.active = 0;
  move_sprite(2, 0, 0);
  move_sprite(3, 0, 0);
}

void init_transmission(unsigned char dir, struct Vector *pos) {
  pewpew();
  
  transmission.active = 1;
  
  transmission.position.x = pos->x;
  transmission.position.y = pos->y;
  
  set_velocity(dir, &transmission.velocity);
  transmission.velocity.x *= 2;
  transmission.velocity.y *= 2;
  
  set_sprite_tile(2, 64);
  set_sprite_tile(3, 66);
  move_transmission();
}

void update_transmission() { 
  if(transmission.animation < 1) {
	// Our transmission reached an objective
	if(tile_at(&transmission.position) == tile_objective_inactive) {
	  toggle_objective(&transmission.position);
	  disable_transmission();
	  return;
	}

	// Or transmission hit a wall
	if(tile_at_next(&transmission.position, &transmission.velocity, 8) > tile_objective_inactive) {
	  disable_transmission();
	  return;
	}
	
	transmission.animation = 8;
  } 
  
  transmission.position.x = transmission.position.x + transmission.velocity.x;
  transmission.position.y = transmission.position.y + transmission.velocity.y;
  move_transmission();
  transmission.animation--;
}
