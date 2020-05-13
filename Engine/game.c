#include "game.h"

void update_game(Input* input, Render_Buffer buffer) {
	static int x_pos = 10;
	static int y_pos = 10;
	
	if (input->buttons[BUTTON_LEFT].is_down && input->buttons[BUTTON_LEFT].changed) {
		x_pos -= 10;
	}
	else if (input->buttons[BUTTON_RIGHT].is_down && input->buttons[BUTTON_RIGHT].changed) {
		x_pos += 10;
	}
	else if (input->buttons[BUTTON_UP].is_down && input->buttons[BUTTON_UP].changed) {
		y_pos += 10;
	}
	else if (input->buttons[BUTTON_DOWN].is_down && input->buttons[BUTTON_DOWN].changed) {
		y_pos -= 10;
	}

	draw_rect(buffer, 0xFF0000, x_pos, y_pos, 100+x_pos, 100 + y_pos);
	draw_line(buffer, 0xFF00FF, 0, 0, 100, 100);
}