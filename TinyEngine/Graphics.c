#include "pch.h"
#include "Graphics.h"

static void draw_single(const Graphics* self, wchar_t ch, Point a);
static void draw_single_c(const Graphics* self, wchar_t ch, Point a, ConsoleColor color);
static void draw_dot_anti_alias(const Graphics* self, Point a);
static void draw_dot_anti_alias_c(const Graphics* self, Point a, ConsoleColor color);
static void draw_line(const Graphics* self, wchar_t ch, Point a, Point b);
static void draw_line_c(const Graphics* self, wchar_t ch, Point a, Point b, ConsoleColor color);
static void draw_line_anti_alias(const Graphics* self, Point a, Point b);
static void draw_line_anti_alias_c(const Graphics* self, Point a, Point b, ConsoleColor color);
static void draw_string(const Graphics* self, const wchar_t str, Point position);
static void draw_string_c(const Graphics* self, const wchar_t str, Point position, ConsoleColor color);
static void draw_framebuffer(const Graphics* self, const FrameBuffer frame_buffer, Point position);
static void draw_framebuffer_c(const Graphics* self, const FrameBuffer frame_buffer, Point position, ConsoleColor color);

const impl_Graphics* get_impl_Graphics_table() {
	static impl_Graphics impl_Graphics_table = {
		.draw_single = draw_single,
		.draw_single_c = draw_single_c,
		.draw_dot_anti_alias = draw_dot_anti_alias,
		.draw_dot_anti_alias_c = draw_dot_anti_alias_c,
		.draw_line = draw_line,
		.draw_line_c = draw_line_c,
		.draw_line_anti_alias = draw_line_anti_alias,
		.draw_line_anti_alias_c = draw_line_anti_alias_c,
		.draw_string = draw_string,
		.draw_string_c = draw_string_c,
		.draw_framebuffer = draw_framebuffer,
		.draw_framebuffer_c = draw_framebuffer_c
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

static void draw_single(const Graphics* self, wchar_t ch, Point a) {

}

static void draw_single_c(const Graphics* self, wchar_t ch, Point a, ConsoleColor color) {

}

static void draw_dot_anti_alias(const Graphics* self, Point a) {

}

static void draw_dot_anti_alias_c(const Graphics* self, Point a, ConsoleColor color) {

}

static void draw_line(const Graphics* self, wchar_t ch, Point a, Point b) {

}

static void draw_line_c(const Graphics* self, wchar_t ch, Point a, Point b, ConsoleColor color) {

}

static void draw_line_anti_alias(const Graphics* self, Point a, Point b) {

}

static void draw_line_anti_alias_c(const Graphics* self, Point a, Point b, ConsoleColor color) {

}

static void draw_string(const Graphics* self, const wchar_t str, Point position) {

}

static void draw_string_c(const Graphics* self, const wchar_t str, Point position, ConsoleColor color) {

}

static void draw_framebuffer(const Graphics* self, const FrameBuffer frame_buffer, Point position) {

}

static void draw_framebuffer_c(const Graphics* self, const FrameBuffer frame_buffer, Point position, ConsoleColor color) {

}
