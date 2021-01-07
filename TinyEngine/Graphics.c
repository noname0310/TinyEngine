#include "pch.h"
#include "Graphics.h"

static void draw_single(const Graphics* self, wchar_t ch, Point a, int thickness);
static void draw_circle(const Graphics* self, wchar_t ch, Point a, int radius);
static void draw_line(const Graphics* self, wchar_t ch, Point a, Point b);
static void draw_string(const Graphics* self, const wchar_t str[], Point position);
static void draw_framebuffer(const Graphics* self, const FrameBuffer* frame_buffer, Point position);

const impl_Graphics* get_impl_Graphics_table() {
	static impl_Graphics impl_Graphics_table = {
		.draw_single = draw_single,
		.draw_circle = draw_circle,
		.draw_line = draw_line,
		.draw_string = draw_string,
		.draw_framebuffer = draw_framebuffer
	};

	if (*(void**)&impl_Graphics_table == NULL) {
		OOPTool.set_const_value(&impl_Graphics_table, get_impl_FrameBuffer_table(), sizeof(impl_FrameBuffer));
	}

	return &impl_Graphics_table;
}

Graphics Graphics_new(int width, int height) {
	FrameBuffer parent_instance = FrameBuffer_new(width, height);

	Graphics instance = {
		.f = get_impl_Graphics_table()
	};

	OOPTool.set_const_value((size_t*)(&instance) + 1, (size_t*)(&parent_instance) + 1, sizeof(FrameBuffer) - sizeof(size_t));
	return instance;
}

static void draw_single(const Graphics* self, wchar_t ch, Point a, int thickness) {
	assert(self != NULL);
	assert(!(thickness <= 0) || !"thickness must be higher than 0");

	if (thickness == 1) {
		self->f->set_pixel((FrameBuffer*)self, a.x, a.y, ch);
		return;
	}

	thickness -= 1;

	int xk = 0;
	int yk = thickness;
	int pk = 3 - (thickness + thickness);

	do {
		int axkt = a.x + xk;
		for (int i = a.x - xk; i <= axkt; i++) {
			self->f->set_pixel((FrameBuffer*)self, i, a.y - yk, ch);
			self->f->set_pixel((FrameBuffer*)self, i, a.y + yk, ch);
		}
		int aykt = a.y + xk;
		for (int i = a.y - xk; i <= aykt; i++) {
			self->f->set_pixel((FrameBuffer*)self, a.x - yk, i, ch);
			self->f->set_pixel((FrameBuffer*)self, a.x + yk, i, ch);
		}

		xk += 1;
		if (pk < 0) pk += (xk << 2) + 6;
		else {
			yk -= 1;
			pk += ((xk - yk) << 2) + 10;

		}

	} while (xk <= yk);

	int axxkm1 = a.x + xk - 1;
	int ayyk = a.y + yk;

	for (int i = a.y - yk; i <= ayyk; i++) {
		for (int j = a.x - xk + 1; j <= axxkm1; j++) {
			self->f->set_pixel((FrameBuffer*)self, j, i, ch);
		}
	}
}

static void draw_circle(const Graphics* self, wchar_t ch, Point a, int radius) {
	assert(self != NULL);
	assert(!(radius <= 0) || !"radius must be higher than 0");

	if (radius == 1) {
		self->f->set_pixel((FrameBuffer*)self, a.x, a.y, ch);
		return;
	}

	radius -= 1;

	int xk = 0;
	int yk = radius;
	int pk = 3 - (radius + radius);

	do {
		self->f->set_pixel((FrameBuffer*)self, a.x + xk, a.y - yk, ch);
		self->f->set_pixel((FrameBuffer*)self, a.x - xk, a.y - yk, ch);
		self->f->set_pixel((FrameBuffer*)self, a.x + xk, a.y + yk, ch);
		self->f->set_pixel((FrameBuffer*)self, a.x - xk, a.y + yk, ch);
		self->f->set_pixel((FrameBuffer*)self, a.x + yk, a.y - xk, ch);
		self->f->set_pixel((FrameBuffer*)self, a.x + yk, a.y + xk, ch);
		self->f->set_pixel((FrameBuffer*)self, a.x - yk, a.y - xk, ch);
		self->f->set_pixel((FrameBuffer*)self, a.x - yk, a.y + xk, ch);
		xk += 1;
		if (pk < 0) pk += (xk << 2) + 6;
		else {
			yk -= 1;
			pk += ((xk - yk) << 2) + 10;
		}

	} while (xk <= yk);
}

//https://gist.github.com/bert/1085538
static void draw_line(const Graphics* self, wchar_t ch, Point a, Point b) {
	assert(self != NULL);

	int dx = Mathf.abs_i32(b.x - a.x);
	int sx = a.x < b.x ? 1 : -1;
	int dy = -Mathf.abs_i32(b.y - a.y);
	int sy = a.y < b.y ? 1 : -1;
	int err = dx + dy, e2;

	loop {
		self->f->set_pixel((FrameBuffer*)self, a.x, a.y, ch);
		if (a.x == b.x && a.y == b.y) break;
		e2 = 2 * err;
		if (e2 >= dy) { 
			err += dy;
			a.x += sx; 
		}
		if (e2 <= dx) { 
			err += dx;
			a.y += sy; 
		}
	}
}

static void draw_string(const Graphics* self, const wchar_t str[], Point position) {
	assert(self != NULL);

	wchar_t* wcp;
	int x = position.x;
	int stri = 0;
	loop {
		if (str[stri] == L'\0')
			break;
		wcp = self->f->get_pixel((FrameBuffer*)self, x, position.y);
		if (wcp == NULL)
			break;
		*wcp = str[stri];

		stri += 1;
		if (127 < str[stri])
			x += 2;
		else
			x += 1;
	}
}

static void draw_framebuffer(const Graphics* self, const FrameBuffer* frame_buffer, Point position) {
	assert(self != NULL);
	assert(frame_buffer != NULL);

	int frame_buffer_height = frame_buffer->f->get_height(frame_buffer);
	int self_buffer_height = self->f->get_height((const FrameBuffer*)self);
	int frame_buffer_width = frame_buffer->f->get_width(frame_buffer);
	int self_buffer_width = self->f->get_width((const FrameBuffer*)self);

	int source_x;
	if (position.x < 0) {
		source_x = -position.x;
		position.x = 0;
	}
	else
		source_x = 0;

	int source_y;
	if (position.y < 0) {
		source_y = -position.y;
		position.y = 0;
	}
	else
		source_y = 0;

	size_t height = (position.y + frame_buffer_height < self_buffer_height) ? frame_buffer_height : self_buffer_height;
	size_t width = (position.x + frame_buffer_width < self_buffer_width) ? frame_buffer_width : self_buffer_width;

	wchar_t* self_buffer = self->buffer;
	wchar_t* source_buffer = frame_buffer->buffer;

	int current_y = source_y;
	for (size_t i = position.y; i < height; i++)
	{
		int current_x = source_x;
		for (size_t j = position.x; j < width; j++) {
			self_buffer[i + j * self_buffer_width] = source_buffer[current_x + current_y * frame_buffer_width];
			current_x += 1;
		}
		current_y += 1;
	}
}