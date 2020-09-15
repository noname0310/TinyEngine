#pragma once

#include <assert.h>
#include "TinyEngine.h"

struct private_Vector2;
typedef struct private_Vector2 private_Vector2;

struct impl_Vector2;
typedef struct impl_Vector2 impl_Vector2;

struct Vector2;
typedef struct Vector2 Vector2;

struct private_Vector2 {
	int x;
	int y;
};

struct impl_Vector2 {
	int (*get_x)(const Vector2* self);
	int (*get_y)(const Vector2* self);
};

struct Vector2 {
	private_Vector2 p;
	const impl_Vector2* const f;
};

TINYENGINE_API Vector2 Vector2_new(int x, int y);