UBYTE joypad_prev;

struct Cursor {
  unsigned char row;
  unsigned char col;
} cursor;

//topleft = 3,3 screen coord

void cursor_update() {
  UBYTE keys, diff;
  int cx, cy, update_pos;
  int row_min = 0;
  int row_max = 4;
  int col_min = 0;
  int col_max = 3;
  
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
	  //case J_A: tower_place(cursor.col, cursor.row); break;
	}
	
	update_pos = 1;
  }
  
  if(update_pos) {
	cx = 16 + cursor.col * 24;
	cy = 16 + cursor.row * 24;
	//cy = 16 + cursor.row * 24 - offset_y;

	move_sprite(0, cx, cy);
	//move_sprite(1, cx + 16, cy);
	//move_sprite(2, cx, cy + 8);
	//move_sprite(3, cx + 16, cy + 8);
  }
}

void cursor_init() {
	// do something here
}
