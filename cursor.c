struct Cursor {
  unsigned char row;
  unsigned char col;
} cursor;

int cursor_update() {
  UBYTE keys, diff;
  int cx, cy, update_pos;
  
  //constants
  int row_min = 0;
  int row_max = 3;
  int col_min = 0;
  int col_max = 4;
  
  int sprite_x_size = 8;
  int sprite_y_size = 16;
  
  keys = joypad();
  
  if(keys != joypad_prev) {
	
	//calculate which key changed
	diff = (joypad_prev ^ keys) & keys;
	joypad_prev = keys;
	
	switch(diff) {
	  case J_UP: if(cursor.row > row_min) cursor.row--; break;
	  case J_DOWN: if(cursor.row < row_max) cursor.row++; break;
	  case J_LEFT: if(cursor.col > col_min) cursor.col--; break;
	  case J_RIGHT: if(cursor.col < col_max) cursor.col++; break;
	  case J_A: set_command(cursor.row, cursor.col, 1); return 1;
	  case J_B: set_command(cursor.row, cursor.col, -1); return 1;
	  case J_SELECT: init_level(); return 0;
	}
	
	update_pos = 1;
  }
  
  if(update_pos) {
	cx = (sprite_x_size * 3) + (cursor.col * 24);
	cy = (sprite_y_size * 2) + (cursor.row * 24);
	
	if (cursor.row > 1) {
	  cy += 8;
	}
	
	if (cursor.row > 2) {
	  cy += 8;
	}

	//top-left
	move_sprite(0, cx, cy);
	
	//bottom-left
	move_sprite(1, cx, cy + 16);
	
	//top-right
	move_sprite(2, cx + 24, cy);
	
	//bottom-right
	move_sprite(3, cx + 24, cy + 16);
	
	//top-left edge
	move_sprite(4, cx + 8, cy);
	
	//top-right edge
	move_sprite(5, cx + 16, cy);
	
	//bottom-left edge
	move_sprite(6, cx + 8, cy + 16);
	
	//bottom-right edge
	move_sprite(7, cx + 16, cy + 16);
  }
  
  return 0;
}

void cursor_init() {
  cursor.row = 0;
  cursor.col = 0;
  
  //0 topleft corner + left edge
  //2 top edge + center blank tile
  
  //corners
  set_sprite_tile(0, 0);
  
  set_sprite_tile(1, 0);
  set_sprite_prop(1, S_FLIPY);
  
  set_sprite_tile(2, 0);
  set_sprite_prop(2, S_FLIPX);
  
  set_sprite_tile(3, 0);
  set_sprite_prop(3, S_FLIPX | S_FLIPY);
  
  //edges
  set_sprite_tile(4, 2);
  
  set_sprite_tile(5, 2);
  set_sprite_prop(5, S_FLIPX);
  
  set_sprite_tile(6, 2);
  set_sprite_prop(6, S_FLIPY);
  
  set_sprite_tile(7, 2);
  set_sprite_prop(7, S_FLIPX | S_FLIPY);
  
  joypad_prev = joypad();
  cursor_update();
}
