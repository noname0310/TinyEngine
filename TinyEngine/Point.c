#include "pch.h"
#include "Point.h"

static void offset(Point* self, Point* point);
static const wchar_t* to_string(const Point* self);
static Point add(const Point* self, const Point* other);
static Point sub(const Point* self, const Point* other);
static bool equals(const Point* self, const Point* other);
static bool not_equals(const Point* self, const Point* other);

const impl_Point* get_impl_Point_table() {
	static impl_Point impl_Point_table = {
		.offset = offset,
		.to_string = to_string,
		.add = add,
		.sub = sub,
		.equals = equals,
		.not_equals = not_equals
	};

	return &impl_Point_table;
}

Point Point_new(int x, int y) {
	Point instance = {
		.f = get_impl_Point_table(),
		.x = x,
		.y = y
	};

	return instance;
}

static void offset(Point* self, Point* point) {
	assert(self != NULL);
	assert(point != NULL);
	self->x += point->x;
	self->y += point->y;
}

static const wchar_t* to_string(const Point* self){
	assert(self != NULL);
	wchar_t str[128];
	swprintf_s(str, 128, L"%d, %d", self->x, self->y);
	box_byref(wchar_t*, str, sizeof(str))
	return (const wchar_t*)str_boxed;
}

static Point add(const Point* self, const Point* other){
	assert(self != NULL);
	assert(other != NULL);
	return Point_new(self->x + other->x, self->x + other->y);
}

static Point sub(const Point* self, const Point* other){
	assert(self != NULL);
	assert(other != NULL);
	return Point_new(self->x - other->x, self->x - other->y);
}

static bool equals(const Point* self, const Point* other){
	assert(self != NULL);
	assert(other != NULL);
	return self->x == other->x && self->x == other->y;
}

static bool not_equals(const Point* self, const Point* other){
	assert(self != NULL);
	assert(other != NULL);
	return !(self->x == other->x && self->x == other->y);
}
