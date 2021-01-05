#pragma once

#include "TinyEngine.h"
#include "FrameBuffer.h"

struct impl_Graphics;
typedef struct impl_Graphics impl_Graphics;

struct Graphics;
typedef struct Graphics Graphics;

struct impl_Graphics {
	impl_FrameBuffer_Members

	void (*const draw_single)(const Graphics* self, wchar_t ch, Point a);
	void (*const draw_single_c)(const Graphics* self, wchar_t ch, Point a, ConsoleColor color);
	void (*const draw_dot_anti_alias)(const Graphics* self, Point a);
	void (*const draw_dot_anti_alias_c)(const Graphics* self, Point a, ConsoleColor color);
	void (*const draw_line)(const Graphics* self, wchar_t ch, Point a, Point b);
	void (*const draw_line_c)(const Graphics* self, wchar_t ch, Point a, Point b, ConsoleColor color);
	void (*const draw_line_anti_alias)(const Graphics* self, Point a, Point b);
	void (*const draw_line_anti_alias_c)(const Graphics* self, Point a, Point b, ConsoleColor color);
	void (*const draw_string)(const Graphics* self, const wchar_t str, Point position);
	void (*const draw_string_c)(const Graphics* self, const wchar_t str, Point position, ConsoleColor color);
	void (*const draw_framebuffer)(const Graphics* self, const FrameBuffer frame_buffer, Point position);
	void (*const draw_framebuffer_c)(const Graphics* self, const FrameBuffer frame_buffer, Point position, ConsoleColor color);
};

struct Graphics {
	const impl_Graphics* const f;
	FrameBuffer_Members
};

API Graphics Graphics_new(int width, int height);
API const impl_Graphics* get_impl_Graphics_table();
