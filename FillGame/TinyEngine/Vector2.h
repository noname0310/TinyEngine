#pragma once

#include "TinyEngine.h"

struct _impl_Vector2;
typedef struct _impl_Vector2 impl_Vector2;

struct private_Vector2;
typedef struct private_Vector2 private_Vector2;

struct Vector2;
typedef struct Vector2 Vector2;

struct _impl_Vector2 {
	//int get_x(Vector2* self)
	int (*get_x)(Vector2*);

	//int get_y(Vector2* self)
	int (*get_y)(Vector2*);
};

struct private_Vector2 {
	int x;
	int y;
};

struct Vector2 {
	private_Vector2 p;
	impl_Vector2* f;
};

TINYENGINE_API Vector2 Vector2_new(int x, int y);