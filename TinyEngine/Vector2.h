#pragma once

#include "Encapsulation.h"

struct _impl_Vector2;
typedef struct _impl_Vector2 impl_Vector2;

struct Vector2;
typedef struct Vector2 Vector2;

struct _impl_Vector2 {
	//int get_x(Vector2* self)
	int (*get_x)(Vector2*);

	//int get_y(Vector2* self)
	int (*get_y)(Vector2*);
};

struct Vector2 {
	private_8byte p8;
	impl_Vector2* f;
};

Vector2 Vector2_new(int x, int y);