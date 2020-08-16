#pragma once

#include "TinyEngine.h"
#include "Encapsulation.h"

//i32 * 2 + p
#ifdef _WIN64
	#define VECTOR2_SIZE 16 
#else
	#define VECTOR2_SIZE 12
#endif

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
	private_(8) p8;
	impl_Vector2* f;
};

TINYENGINE_API Vector2 Vector2_new(int x, int y);