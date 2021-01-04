#pragma once

#include "TinyEngine.h"
#include "Console.h"

struct private_FrameBuffer;
typedef struct private_FrameBuffer private_FrameBuffer;

struct impl_FrameBuffer;
typedef struct impl_FrameBuffer impl_FrameBuffer;

struct FrameBuffer;
typedef struct FrameBuffer FrameBuffer;

struct private_FrameBuffer {
	int width;
	int height;
};

struct impl_FrameBuffer {
	void (*const change_scale)(FrameBuffer* self, int width, int height);
	int (*const get_height)(const FrameBuffer* self);
	int (*const get_width)(const FrameBuffer* self);
	void (*const for_each)(const FrameBuffer* self, void (*fn)(int x, int y, wchar_t* item));
	void (*const dispose)(FrameBuffer* self);
};

struct FrameBuffer {
	const impl_FrameBuffer* const f;
	private_FrameBuffer private_Object;
	wchar_t* buffer;
};

API FrameBuffer FrameBuffer_new(int width, int height);
API const impl_FrameBuffer* get_impl_FrameBuffer_table();
