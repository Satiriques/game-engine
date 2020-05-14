#include "software_rendering.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void clear_screen(Render_Buffer buffer, uint32_t color) {
	uint32_t* pixels = buffer.pixels;

	for (int i = 0; i < buffer.height; i++) {
		for (int j = 0; j < buffer.width; j++) {
			*pixels++ = color;
		}
	}
}

void draw_rect_in_pixels(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2)
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

void draw_rect(Render_Buffer buffer, v2 p, v2 half_size, uint32_t color){
	float aspect_multiplier = (float)buffer.width;
	float scale = 0.001f;

	if ((float)buffer.width / (float)buffer.height < 1.77f)
		aspect_multiplier = (float)buffer.height / 1.77f;

	half_size.x *= aspect_multiplier * scale;
	half_size.y *= aspect_multiplier * scale;

	p.x *= aspect_multiplier * scale;
	p.y *= aspect_multiplier * scale;

	// centers the coordinates
	p.x += (float)buffer.width * .5f;
	p.y += (float)buffer.height * .5f;

	// gets the x and y around the center point
	int x1 = (int)(p.x - half_size.x);
	int y1 = (int)(p.y - half_size.y);
	int x2 = (int)(p.x + half_size.x);
	int y2 = (int)(p.y + half_size.y);

	draw_rect_in_pixels(buffer, color, x1, y1, x2, y2);
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
void draw_line_in_pixels(Render_Buffer buffer, uint32_t color, int x1, int y1, int x2, int y2) {
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

void reverse_range(uint8_t* buffer, int left, int right)
{
	while (left < right)
	{
		int temp = buffer[left];
		buffer[left++] = buffer[right];
		buffer[right--] = temp;
	}
}

void draw_bitmap(Render_Buffer buffer, char* file, int x1, int y1, uint32_t transparency) {
	int width, height, bpp, y, x;

	uint8_t* image = stbi_load(file, &width, &height, &bpp, 3);

	//to do: fix algo so this is not needed
	reverse_range(image, 0, width * height * 3 - 1);

	for (int i = 0; i < width * height * 3; i += 3) {
		uint32_t color = image[i] | image[i + 1] << 8 | image[i + 2] << 16;
		y = y1 + (i / 3 / width);
		x = x1 + i / 3 % width;
		if (color != transparency) {
			draw_pixel(buffer, color, x, y);
		}

	}

	stbi_image_free(image);
}






