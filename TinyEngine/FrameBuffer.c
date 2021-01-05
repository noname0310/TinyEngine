#include "pch.h"
#include "FrameBuffer.h"

static void change_scale(FrameBuffer* self, int width, int height);
static int get_height(const FrameBuffer* self);
static int get_width(const FrameBuffer* self);
static wchar_t* get_pixel(const FrameBuffer* self, int x, int y);
static void set_pixel(const FrameBuffer* self, int x, int y, wchar_t ch);
static void clear(const FrameBuffer* self);
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
		.get_pixel = get_pixel,
		.set_pixel = set_pixel,
		.clear = clear,
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
	assert(4 <= buffer_size);
	for (size_t i = 0; i < buffer_count; i++)
		buffer[i] = L' ';

	FrameBuffer instance = {
		.f = get_impl_FrameBuffer_table(),
		.private_FrameBuffer = p_instance,
		.buffer = buffer
	};

	return instance;
}

static void change_scale(FrameBuffer* self, int width, int height) {
	assert(self != NULL);
	if (width <= 0 || height <= 0)
		assert(!"width and height cannot be lower than 1");

	int sq = width * height;
	int sq_size = sq * sizeof(wchar_t);
	if (self->private_FrameBuffer.width * self->private_FrameBuffer.height != sq) {
		wchar_t* new_buffer = realloc(self->buffer, sq_size);
		if (new_buffer != NULL)
			self->buffer = new_buffer;

		wchar_t* buffer = self->buffer;
		assert(4 <= sq_size);
		for (int i = 0; i < sq; i++)
			buffer[i] = L' ';

		wchar_t* new_prev_buffer = realloc(self->private_FrameBuffer.prev_buffer, sq * sizeof(wchar_t));
		if (new_prev_buffer != NULL)
			self->private_FrameBuffer.prev_buffer = new_prev_buffer;

		refresh(self);
	}
	self->private_FrameBuffer.width = width;
	self->private_FrameBuffer.height = height;
}

static int get_height(const FrameBuffer* self) {
	assert(self != NULL);
	return self->private_FrameBuffer.height;
}

static int get_width(const FrameBuffer* self) {
	assert(self != NULL);
	return self->private_FrameBuffer.width;
}

static wchar_t* get_pixel(const FrameBuffer* self, int x, int y) {
	assert(self != NULL);
	if (x < 0 || self->private_FrameBuffer.width <= x || y < 0 || self->private_FrameBuffer.height <= y)
		return NULL;
	return &self->buffer[x + y * self->private_FrameBuffer.width];
}

static void set_pixel(const FrameBuffer* self, int x, int y, wchar_t ch) {
	assert(self != NULL);
	if (x < 0 || self->private_FrameBuffer.width <= x || y < 0 || self->private_FrameBuffer.height <= y)
		return;
	self->buffer[x + y * self->private_FrameBuffer.width] = ch;
}

static void clear(const FrameBuffer* self) {
	assert(self != NULL);
	int width = self->private_FrameBuffer.width;
	int height = self->private_FrameBuffer.height;
	size_t buffer_count = (size_t)width * (size_t)height;
	wchar_t* buffer = self->buffer;

	for (size_t i = 0; i < buffer_count; i++) {
		buffer[i] = L' ';
	}
}

static void for_each(const FrameBuffer* self, void (*fn)(Point index, wchar_t* item)) {
	assert(self != NULL);
	int width = self->private_FrameBuffer.width;
	int height = self->private_FrameBuffer.height;

	wchar_t* buffer = self->buffer;
	
	int index = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fn(Point_new((int)j, (int)i), &buffer[index]);
			index += 1;
		}
	}
}

static void for_each_c(const FrameBuffer* self, void (*fn)(Point index, wchar_t item)) {
	assert(self != NULL);
	assert(fn != NULL);
	int width = self->private_FrameBuffer.width;
	int height = self->private_FrameBuffer.height;
	wchar_t* buffer = self->buffer;

	int index = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fn(Point_new((int)j, (int)i), buffer[index]);
			index += 1;
		}
	}
}

static void print(FrameBuffer* self) {
	assert(self != NULL);
	int width = self->private_FrameBuffer.width;
	int height = self->private_FrameBuffer.height;
	wchar_t* buffer = self->buffer;
	wchar_t* prev_buffer = self->private_FrameBuffer.prev_buffer;

	int index = 0;

	for (int i = 0; i < height; i++) {
		int lastj = 0;

		for (int j = 0; j < width; j++) {
			if (buffer[index] == prev_buffer[index]) {
				index += 1;
				continue;
			}

			if (!(lastj + 1 == j && j + 1 == width))
				Console.set_pos((short)j, (short)i);
			lastj = j;
			Console.write_single(buffer[index]);
			
			if (127 < prev_buffer[index] && prev_buffer[index + 1] <= 127)
				Console.write_single(buffer[index]);

			prev_buffer[index] = buffer[index];
			index += 1;
		}
	}
}

static void refresh(const FrameBuffer* self) {
	assert(self != NULL);
	memset(self->private_FrameBuffer.prev_buffer, 0, (size_t)self->private_FrameBuffer.width * (size_t)self->private_FrameBuffer.height * sizeof(wchar_t));
}

static void dispose(FrameBuffer* self) {
	assert(self != NULL);
	free(self->buffer);
}
