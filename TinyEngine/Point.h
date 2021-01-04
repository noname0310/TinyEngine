#pragma once

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "TinyEngine.h"
#include "OOPTool.h"

struct impl_Point;
typedef struct impl_Point impl_Point;

struct Point;
typedef struct Point Point;

struct impl_Point {
	void (*const offset)(Point* self, Point* point);
	const wchar_t* (*const to_string)(const Point* self);
	Point (*const add)(const Point* self, const Point* other);
	Point (*const sub)(const Point* self, const Point* other);
	bool (*const equals)(const Point* self, const Point* other);
	bool (*const not_equals)(const Point* self, const Point* other);
};

struct Point {
	const impl_Point* const f;
	int x;
	int y;
};

API Point Point_new(int x, int y);
API const impl_Point* get_impl_Point_table();