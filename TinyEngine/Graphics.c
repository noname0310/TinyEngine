#include "pch.h"
#include "Graphics.h"

static void draw_single(const Graphics* self, wchar_t ch, Point a, int thickness);
static void draw_dot_anti_alias(const Graphics* self, Point a, int thickness);
static void draw_circle(const Graphics* self, wchar_t ch, Point a, int radius);
static void draw_circle_anti_alias(const Graphics* self, wchar_t ch, Point a, int radius);
static void draw_line(const Graphics* self, wchar_t ch, Point a, Point b, int thickness);
static void draw_line_anti_alias(const Graphics* self, Point a, Point b, int thickness);
static void draw_string(const Graphics* self, const wchar_t str[], Point position);
static void draw_framebuffer(const Graphics* self, const FrameBuffer* frame_buffer, Point position);

const impl_Graphics* get_impl_Graphics_table() {
	static impl_Graphics impl_Graphics_table = {
		.draw_single = draw_single,
		.draw_dot_anti_alias = draw_dot_anti_alias,
		.draw_circle = draw_circle,
		.draw_circle_anti_alias = draw_circle_anti_alias,
		.draw_line = draw_line,
		.draw_line_anti_alias = draw_line_anti_alias,
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

static void draw_dot_anti_alias(const Graphics* self, Point a, int thickness) {
	assert(self != NULL);
	assert(!(thickness <= 0) || !"thickness must be higher than 0");
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

static void draw_circle_anti_alias(const Graphics* self, wchar_t ch, Point a, int radius) {
	assert(self != NULL);
	assert(!(radius <= 0) || !"radius must be higher than 0");
}

static void draw_line(const Graphics* self, wchar_t ch, Point a, Point b, int thickness) {
	assert(self != NULL);
	assert(!(thickness <= 0) || !"thickness must be higher than 0");

	wchar_t* wcp;
	self->f->set_pixel((FrameBuffer*)self, a.x, a.y, ch);
	int delx = Mathf.abs_i32(b.x - a.x);
	int dely = Mathf.abs_i32(b.y - a.y);
	int p = (2 * delx) - dely;
	for (int i = 0; i < delx; i++) {
		if (p < 0) {
			a.y = a.y + 1;
			self->f->set_pixel((FrameBuffer*)self, a.x, a.y, ch);
			p = p + (2 * delx);
		}
		else {
			a.x = a.x + 1;
			a.y = a.y + 1;
			self->f->set_pixel((FrameBuffer*)self, a.x, a.y, ch);
			p = p + (2 * delx) - (2 * dely);
		}
	}
}

static void draw_line_anti_alias(const Graphics* self, Point a, Point b, int thickness) {
	assert(self != NULL);
	assert(!(thickness <= 0) || !"thickness must be higher than 0");
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

}