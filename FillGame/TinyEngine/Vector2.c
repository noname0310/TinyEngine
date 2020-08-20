#include "pch.h"
#include "Vector2.h"

static int get_x(const Vector2* self);
static int get_y(const Vector2* self);

impl_Vector2 impl_Vector2_table = {
	.get_x = get_x,
	.get_y = get_y
};

Vector2 Vector2_new(int x, int y) {

	private_Vector2 p_instance = {
		.x = x,
		.y = y
	};

	Vector2 instance = {
		.p = p_instance,
		.f = &impl_Vector2_table
	};

	return instance;
}

static int get_x(const Vector2* self) {
	assert(self != NULL);
	return self->p.x;
}

static int get_y(const Vector2* self) {
	assert(self != NULL);
	return self->p.y;
}