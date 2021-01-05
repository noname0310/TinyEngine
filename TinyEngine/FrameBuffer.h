#pragma once

#include "TinyEngine.h"
#include "Console.h"
#include "Point.h"
#include "OOPTool.h"

struct private_FrameBuffer;
typedef struct private_FrameBuffer private_FrameBuffer;

struct impl_FrameBuffer;
typedef struct impl_FrameBuffer impl_FrameBuffer;

struct FrameBuffer;
typedef struct FrameBuffer FrameBuffer;

struct private_FrameBuffer {
	int width;
	int height;
	wchar_t* prev_buffer;
};

struct impl_FrameBuffer {
#define impl_FrameBuffer_Members \
	void (*const change_scale)(FrameBuffer* self, int width, int height); \
	int (*const get_height)(const FrameBuffer* self); \
	int (*const get_width)(const FrameBuffer* self); \
	void (*const for_each)(const FrameBuffer* self, void (*fn)(Point index, wchar_t* item)); \
	void (*const for_each_c)(const FrameBuffer* self, void (*fn)(Point index, wchar_t item)); \
	void (*const print)(FrameBuffer* self); \
	void (*const refresh)(const FrameBuffer* self); \
	void (*const dispose)(FrameBuffer* self);
	
	impl_FrameBuffer_Members
};

struct FrameBuffer {
	const impl_FrameBuffer* const f;

#define FrameBuffer_Members \
	private_FrameBuffer private_FrameBuffer; \
	wchar_t* buffer;

	FrameBuffer_Members
};

API FrameBuffer FrameBuffer_new(int width, int height);
API const impl_FrameBuffer* get_impl_FrameBuffer_table();
