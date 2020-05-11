#include "software_rendering.h"

void clear_screen(Render_Buffer buffer, uint32_t color) {
	uint32_t* pixels = buffer.pixels;

	for (int i = 0; i < buffer.height; i++) {
		for (int j = 0; j < buffer.width; j++) {
			*pixels++ = color;
		}
	}
}

void draw_rect(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2)
{
	x1 = clamp(0, x1, buffer.width);
	y1 = clamp(0, y1, buffer.height);
	x2 = clamp(0, x2, buffer.width);
	y2 = clamp(0, y2, buffer.height);

	uint32_t* row = buffer.pixels + x1 + buffer.width * y1;
	uint32_t* pixel = row;
	int stride = buffer.width;
	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			*pixel++ = color;
		}
		row += stride;
		pixel = row;
	}
}

void draw_pixel(Render_Buffer buffer, uint32_t color, int x, int y) {
	uint32_t* pixels = buffer.pixels;
	pixels[y * buffer.width + x] = color;
}

/// <summary>
/// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
/// </summary>
/// <param name="buffer"></param>
/// <param name="color"></param>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
void draw_line(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2) {
	double dx = fabs((double)x2 - (double)x1);
	int sx = x1 < x2 ? 1 : -1;
	double dy = -fabs((double)y2 - (double)y1);
	int sy = y1 < y2 ? 1 : -1;
	double err = dx + dy;
	double e2 = 0.0;

	while (true) {
		if (x1 >= 0 && x1 < buffer.width && y1 >= 0 && x1 < buffer.height) {
			draw_pixel(buffer, color, x1, y1);
		}
		
		if (x1 == x2 && y1 == y2) break;
		e2 = 2 * err;
		if (e2 >= dy) {
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx) {
			err += dx;
			y1 += sy;
		}
	}
}
