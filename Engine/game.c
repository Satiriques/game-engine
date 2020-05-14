#include "game.h"

v2 player_pos;

void update_game(Input* input, Render_Buffer buffer, float dt) {
	static int x_pos = 10;
	static int y_pos = 10;

	int speed = 100;
	
	if (input->buttons[BUTTON_LEFT].is_down) {
		player_pos.x -= speed * dt;
	}
	if (input->buttons[BUTTON_RIGHT].is_down) {
		player_pos.x += speed * dt;
	}
	if (input->buttons[BUTTON_UP].is_down) {
		player_pos.y += speed * dt;
	}
	if (input->buttons[BUTTON_DOWN].is_down) {
		player_pos.y -= speed * dt;
	}

	draw_rect(buffer, player_pos, (v2) { 10, 10 }, 0x00FF00);
	//draw_rect_in_pixels(buffer, 0xFF0000, x_pos, y_pos, 100+x_pos, 100 + y_pos);
	draw_line_in_pixels(buffer, 0xFF00FF, 0, 0, 100, 100);
}