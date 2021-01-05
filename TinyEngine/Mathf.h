#pragma once

#include <stdbool.h>
#include <assert.h>
#include "TinyEngine.h"

struct _Mathf;
typedef struct _Mathf _Mathf;

struct _Mathf {
	const float Epsilon;
	const float PI;
	const float Infinity;
	const float NegativeInfinity;
	const float Deg2Rad;
	const float Rad2Deg;
	float (*const sin)(float f);
	float (*const cos)(float f);
	float (*const tan)(float f);
	float (*const asin)(float f);
	float (*const acos)(float f);
	float (*const atan)(float f);
	float (*const atan2)(float y, float x);
	float (*const sqrt)(float f);
	float (*const abs)(float f);
	int (*const abs_i32)(int f);
	float (*const min)(float a, float b);
	float (*const min_args)(int count, ...);
	int (*const min_i32)(int a, int b);
	int (*const min_i32_args)(int count, ...);
	float (*const max)(float a, float b);
	float (*const max_args)(int count, ...);
	int (*const max_i32)(int a, int b);
	int (*const max_i32_args)(int count, ...);
	float (*const pow)(float f, float p);
	float (*const exp)(float power);
	float (*const log)(float f, float p);
	float (*const log_e)(float f);
	float (*const log_10)(float f);
	float (*const ceil)(float f);
	float (*const floor)(float f);
	float (*const round)(float f);
	int (*const ceil_to_int)(float f);
	int (*const floor_to_int)(float f);
	int (*const round_to_int)(float f);
	float (*const sign)(float f);
	float (*const clamp)(float value, float min, float max);
	int (*const clamp_i32)(int value, int min, int max);
	float (*const clamp_01)(float value);
	float (*const lerp)(float a, float b, float t);
	float (*const lerp_unclamped)(float a, float b, float t);
	float (*const lerp_angle)(float a, float b, float t);
	float (*const move_towards)(float current, float target, float max_delta);
	float (*const move_towards_angle)(float current, float target, float max_delta);
	float (*const smooth_step)(float from, float to, float t);
	float (*const gamma)(float value, float absmax, float gamma);
	bool (*const approximately)(float a, float b);
	float (*const smooth_damp)(float current, float target, float* current_velocity, float smooth_time, float max_speed, float delta_time);
	float (*const smooth_damp_angle)(float current, float target, float* current_velocity, float smooth_time, float max_speed, float delta_time);
	float (*const repeat)(float t, float length);
	float (*const ping_pong)(float t, float length);
	float (*const inverse_lerp)(float a, float b, float value);
	int (*const closest_power_of_two)(int value);
	float (*const gamma_to_linear_space)(float value);
	float (*const linear_to_gamma_space)(float value);
	bool (*const is_power_of_two)(int value);
	int (*const next_power_of_two)(int value);
	float (*const delta_angle)(float current, float target);
	float (*const noise)(float x, float y);
	float (*const perlin_noise)(float x, float y, float freq, int depth);
	unsigned short (*const float_to_half)(float value);
	float (*const half_to_float)(unsigned short value);
};

extern API const _Mathf Mathf;
