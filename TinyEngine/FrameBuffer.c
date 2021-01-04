#include "pch.h"
#include "FrameBuffer.h"

static void change_scale(FrameBuffer* self, int width, int height);
static int get_height(const FrameBuffer* self);
static int get_width(const FrameBuffer* self);
static void for_each(const FrameBuffer* self, void (*fn)(Point index, wchar_t* item));
static void for_each_c(const FrameBuffer* self, void (*fn)(Point index, wchar_t item));
static void print(FrameBuffer* self);
static void refresh(const FrameBuffer* self);
static void dispose(FrameBuffer* self);

const impl_FrameBuffer* get_impl_FrameBuffer_table() {
	static impl_FrameBuffer impl_FrameBuffer_table = {
		.change_scale = change_scale,
		.get_height = get_height,
		.get_width = get_width,
		.for_each = for_each,
		.for_each_c = for_each_c,
		.print = print,
		.refresh = refresh,
		.dispose = dispose
	};

	return &impl_FrameBuffer_table;
}

FrameBuffer FrameBuffer_new(int width, int height) {
	if (width <= 0 || height <= 0)
		assert(!"width and height cannot be lower than 1");

	size_t buffer_count = (size_t)width * (size_t)height;
	size_t buffer_size = buffer_count * sizeof(wchar_t);
	wchar_t* prev_buffer = (wchar_t*)calloc(1, buffer_size);
	assert(prev_buffer != NULL || !"malloc failed");

	private_FrameBuffer p_instance = {
		.width = width,
		.height = height,
		.prev_buffer = prev_buffer
	};

	wchar_t* buffer = (wchar_t*)malloc(buffer_size);
	assert(buffer != NULL || !"malloc failed");
	memset(buffer, ' ', buffer_size);
	assert(4 <= buffer_size);
	for (size_t i = 0; i < buffer_count; i++)
		buffer[i] = L' ';

	FrameBuffer instance = {
		.f = get_impl_FrameBuffer_table(),
		.p = p_instance,
		.buffer = buffer
	};

	return instance;
}

static void change_scale(FrameBuffer* self, int width, int height) {
	if (width <= 0 || height <= 0)
		assert(!"width and height cannot be lower than 1");

	int sq = width * height;
	int sq_size = sq * sizeof(wchar_t);
	if (self->p.width * self->p.height != sq) {
		wchar_t* new_buffer = realloc(self->buffer, sq_size);
		if (new_buffer != NULL)
			self->buffer = new_buffer;

		wchar_t* buffer = self->buffer;
		assert(4 <= sq_size);
		for (size_t i = 0; i < sq; i++)
			buffer[i] = L' ';

		wchar_t* new_prev_buffer = realloc(self->p.prev_buffer, sq * sizeof(wchar_t));
		if (new_prev_buffer != NULL)
			self->p.prev_buffer = new_prev_buffer;

		refresh(self);
	}
	self->p.width = width;
	self->p.height = height;
}

static int get_height(const FrameBuffer* self) {
	return self->p.height;
}

static int get_width(const FrameBuffer* self) {
	return self->p.width;
}

static void for_each(const FrameBuffer* self, void (*fn)(Point index, wchar_t* item)) {
	int width = self->p.width;
	int height = self->p.height;
	wchar_t* buffer = self->buffer;
	
	int index = 0;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			fn(Point_new(j, i), &buffer[index]);
			index += 1;
		}
	}
}

static void for_each_c(const FrameBuffer* self, void (*fn)(Point index, wchar_t item)) {
	int width = self->p.width;
	int height = self->p.height;
	wchar_t* buffer = self->buffer;

	int index = 0;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			fn(Point_new(j, i), buffer[index]);
			index += 1;
		}
	}
}

static void print(FrameBuffer* self) {
	int width = self->p.width;
	int height = self->p.height;
	wchar_t* buffer = self->buffer;
	wchar_t* prev_buffer = self->p.prev_buffer;

	int index = 0;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (buffer[index] == prev_buffer[index]) {
				index += 1;
				continue;
			}

			Console.set_pos(j, i);
			Console.write(L"%c", buffer[index]);
			prev_buffer[index] = buffer[index];
			index += 1;
		}
	}
}

static void refresh(const FrameBuffer* self) {
	memset(self->p.prev_buffer, 0, (size_t)self->p.width * (size_t)self->p.height * sizeof(wchar_t));
}

static void dispose(FrameBuffer* self) {
	free(self->buffer);
}
