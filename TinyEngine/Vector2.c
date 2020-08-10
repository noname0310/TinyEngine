#include "Vector2.h"

struct private_Vector2;
typedef struct private_Vector2 private_Vector2;

struct private_Vector2 {
	int x;
	int y;
};

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
		.p8 = *(private_8byte*)&p_instance,
		.f = &impl_Vector2_table
	};

	return instance;
}

static int Vector2_get_x(Vector2* self) {
	return (*(private_Vector2*)&(self->p8)).x;
}

static int Vector2_get_y(Vector2* self) {
	return (*(private_Vector2*)&(self->p8)).y;
}