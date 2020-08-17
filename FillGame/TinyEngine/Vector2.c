#include "pch.h"
#include "Vector2.h"

static int Vector2_get_x(Vector2* self);
static int Vector2_get_y(Vector2* self);

impl_Vector2 impl_Vector2_table = {
	.get_x = Vector2_get_x,
	.get_y = Vector2_get_y
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

static int Vector2_get_x(Vector2* self) {
	return self->p.x;
}

static int Vector2_get_y(Vector2* self) {
	return self->p.y;
}