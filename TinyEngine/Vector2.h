#pragma once

#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "TinyEngine.h"
#include "OOPTool.h"

struct private_Vector2;
typedef struct private_Vector2 private_Vector2;

struct impl_Vector2;
typedef struct impl_Vector2 impl_Vector2;

struct Vector2;
typedef struct Vector2 Vector2;

struct static_Vector2;
typedef struct static_Vector2 static_Vector2;

struct private_Vector2 {
	float x;
	float y;
};

struct impl_Vector2 {
	float (*const get_x)(const Vector2* self);
	void (*const set_x)(Vector2* self, float value);
	float (*const get_y)(const Vector2* self);
	void (*const set_y)(Vector2* self, float value);
	float (*const magnitude)(const Vector2* self);
	float (*const sqr_magnitude)(const Vector2* self);
	Vector2 (*const normalized)(const Vector2* self);
	void (*const normalize)(Vector2* self);
	void (*const set)(Vector2* self, float x, float y);
	const wchar_t* (*const to_string)(const Vector2* self);
	Vector2(* const add)(const Vector2* self, const Vector2* other);
	Vector2 (*const sub)(const Vector2* self, const Vector2* other);
	Vector2 (*const mul)(const Vector2* self, float d);
	Vector2 (*const div)(const Vector2* self, float d);
	bool (*const equals)(const Vector2* self, const Vector2* other);
	bool (*const not_equals)(const Vector2* self, const Vector2* other);
};

struct Vector2 {
	private_Vector2 p;
	const impl_Vector2* const f;
};

struct static_Vector2 {
	const Vector2 zero;
	const Vector2 one;
	const Vector2 up;
	const Vector2 down;
	const Vector2 left;
	const Vector2 right;
	const Vector2 positiveInfinity;
	const Vector2 negativeInfinity;
	Vector2 (*const add)(const Vector2* a, const Vector2* b);
	Vector2 (*const sub)(const Vector2* a, const Vector2* b);
	Vector2 (*const mul)(const Vector2* a, float d);
	Vector2 (*const div)(const Vector2* a, float d);
	bool (*const equals)(const Vector2* a, const Vector2* b);
	bool (*const not_equals)(const Vector2* a, const Vector2* b);
	Vector2 (*const lerp)(const Vector2* a, const Vector2* b, float t);
	Vector2 (*const lerp_unclamped)(const Vector2* a, const Vector2* b, float t);
	Vector2 (*const move_towards)(const Vector2* current, const Vector2* target, float max_distance_delta);
	Vector2 (*const reflect)(const Vector2* in_direction, const Vector2* in_normal);
	float (*const dot)(const Vector2* lhs, const Vector2* rhs);
	float (*const angle)(const Vector2* from, const Vector2* to);
	float (*const distance)(const Vector2* a, const Vector2* b);
	Vector2 (*const clamp_magnitude)(const Vector2* vector, float max_length);
	float (*const sqr_magnitude)(const Vector2* a);
	Vector2 (*const min)(const Vector2* lhs, const Vector2* rhs);
	Vector2 (*const max)(const Vector2* lhs, const Vector2* rhs);
	Vector2 (*const smooth_damp)(const Vector2* current, const Vector2* target, Vector2* currentVelocity, float smooth_time, float max_speed, float delta_time);
};

TINYENGINE_API Vector2 Vector2_new(float x, float y);
TINYENGINE_API const impl_Vector2* get_impl_Vector2_table();
TINYENGINE_API const static_Vector2* get_static_Vector2_table();
