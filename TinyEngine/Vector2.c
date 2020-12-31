#include "pch.h"
#include "Vector2.h"

static float get_x(const Vector2* self);
static void set_x(Vector2* self, float value);
static float get_y(const Vector2* self);
static void set_y(Vector2* self, float value);
static float magnitude(const Vector2* self);
static float sqr_magnitude(const Vector2* self);
static Vector2 normalized(const Vector2* self);
static void normalize(Vector2* self);
static void set(Vector2* self, float x, float y);
static const wchar_t* to_string(const Vector2* self);
static Vector2 add(const Vector2* self, const Vector2* other);
static Vector2 sub(const Vector2* self, const Vector2* other);
static Vector2 mul(const Vector2* self, float d);
static Vector2 div_value(const Vector2* self, float d);
static bool equals(const Vector2* self, const Vector2* other);
static bool not_equals(const Vector2* self, const Vector2* other);

static Vector2 lerp(const Vector2* a, const Vector2* b, float t);
static Vector2 lerp_unclamped(const Vector2* a, const Vector2* b, float t);
static Vector2 move_towards(const Vector2* current, const Vector2* target, float max_distance_delta);
static Vector2 reflect(const Vector2* in_direction, const Vector2* in_normal);
static float dot(const Vector2* lhs, const Vector2* rhs);
static float angle(const Vector2* from, const Vector2* to);
static float distance(const Vector2* a, const Vector2* b);
static Vector2 clamp_magnitude(const Vector2* vector, float max_length);
static Vector2 min_value(const Vector2* lhs, const Vector2* rhs);
static Vector2 max_value(const Vector2* lhs, const Vector2* rhs);
static Vector2 smooth_damp(const Vector2* current, const Vector2* target, Vector2* currentVelocity, float smooth_time, float max_speed, float delta_time);

const impl_Vector2* get_impl_Vector2_table() {
	static impl_Vector2 impl_Vector2_table = {
		.get_x = get_x,
		.set_x = set_x,
		.get_y = get_y,
		.set_y = set_y,
		.magnitude = magnitude,
		.sqr_magnitude = sqr_magnitude,
		.normalized = normalized,
		.normalize = normalize,
		.set = set,
		.to_string = to_string,
		.add = add,
		.sub = sub,
		.mul = mul,
		.div = div_value,
		.equals = equals,
		.not_equals = not_equals
	};

	return &impl_Vector2_table;
}

const static_Vector2* get_static_Vector2_table() {
	static static_Vector2 static_Vector2_table = {
		.add = add,
		.sub = sub,
		.mul = mul,
		.div = div_value,
		.equals = equals,
		.not_equals = not_equals,
		.lerp = lerp,
		.lerp_unclamped = lerp_unclamped,
		.move_towards = move_towards,
		.reflect = reflect,
		.dot = dot,
		.angle = angle,
		.distance = distance,
		.clamp_magnitude = clamp_magnitude,
		.sqr_magnitude = sqr_magnitude,
		.min = min_value,
		.max = max_value,
		.smooth_damp = smooth_damp
	};

	if (((char**)&static_Vector2_table)[2] == NULL) {
		Vector2 zero = Vector2_new(0, 0);
		Vector2 one = Vector2_new(1, 1);
		Vector2 up = Vector2_new(0, 1);
		Vector2 down = Vector2_new(0, -1);
		Vector2 left = Vector2_new(-1, 0);
		Vector2 right = Vector2_new(1, 0);
		Vector2 positiveInfinity = Vector2_new(INFINITY, INFINITY);
		Vector2 negativeInfinity = Vector2_new(-INFINITY, -INFINITY);

		OOPTool.set_const_value(&static_Vector2_table.zero, &zero, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.one, &one, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.up, &up, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.down, &down, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.left, &right, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.right, &right, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.negativeInfinity, &negativeInfinity, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.positiveInfinity, &positiveInfinity, sizeof(Vector2));
	}

	return (const static_Vector2*)&static_Vector2_table;
}

Vector2 Vector2_new(float x, float y) {
	private_Vector2 p_instance = {
		.x = x,
		.y = y
	};

	Vector2 instance = {
		.p = p_instance,
		.f = get_impl_Vector2_table()
	};

	return instance;
}

static float get_x(const Vector2* self) {
	assert(self != NULL);
	return self->p.x;
}

static void set_x(Vector2* self, float value) {
	assert(self != NULL);
	self->p.x = value;
}

static float get_y(const Vector2* self) {
	assert(self != NULL);
	return self->p.y;
}

static void set_y(Vector2* self, float value) {
	assert(self != NULL);
	self->p.y = value;
}

static float magnitude(const Vector2* self) {
	assert(self != NULL);
}

static float sqr_magnitude(const Vector2* self) {
	assert(self != NULL);
}

static Vector2 normalized(const Vector2* self) {
	assert(self != NULL);
}

static void normalize(Vector2* self) {
	assert(self != NULL);
}

static void set(Vector2* self, float x, float y) {
	assert(self != NULL);
	self->p.x = x;
	self->p.y = y;
}

static const wchar_t* to_string(const Vector2* self) {
	assert(self != NULL);
}

static Vector2 add(const Vector2* self, const Vector2* other) {
	assert(self != NULL);
}

static Vector2 sub(const Vector2* self, const Vector2* other) {
	assert(self != NULL);
}

static Vector2 mul(const Vector2* self, float d) {
	assert(self != NULL);
}

static Vector2 div_value(const Vector2* self, float d) {
	assert(self != NULL);
}

static bool equals(const Vector2* self, const Vector2* other) {
	assert(self != NULL);
}

static bool not_equals(const Vector2* self, const Vector2* other) {
	assert(self != NULL);
}


static Vector2 lerp(const Vector2* a, const Vector2* b, float t) {
	assert(a != NULL);
	assert(b != NULL);
}

static Vector2 lerp_unclamped(const Vector2* a, const Vector2* b, float t) {
	assert(a != NULL);
	assert(b != NULL);
}

static Vector2 move_towards(const Vector2* current, const Vector2* target, float max_distance_delta) {
	assert(current != NULL);
	assert(target != NULL);
}

static Vector2 reflect(const Vector2* in_direction, const Vector2* in_normal) {
	assert(in_direction != NULL);
	assert(in_normal != NULL);
}

static float dot(const Vector2* lhs, const Vector2* rhs) {
	assert(lhs != NULL);
	assert(rhs != NULL);
}

static float angle(const Vector2* from, const Vector2* to) {
	assert(from != NULL);
	assert(to != NULL);
}

static float distance(const Vector2* a, const Vector2* b) {
	assert(a != NULL);
	assert(b != NULL);
}

static Vector2 clamp_magnitude(const Vector2* vector, float max_length) {
	assert(vector != NULL);
}

static Vector2 min_value(const Vector2* lhs, const Vector2* rhs) {
	assert(lhs != NULL);
	assert(rhs != NULL);
}

static Vector2 max_value(const Vector2* lhs, const Vector2* rhs) {
	assert(lhs != NULL);
	assert(rhs != NULL);
}

static Vector2 smooth_damp(const Vector2* current, const Vector2* target, Vector2* currentVelocity, float smooth_time, float max_speed, float delta_time) {
	assert(current != NULL);
	assert(target != NULL);
	assert(currentVelocity != NULL);
}
