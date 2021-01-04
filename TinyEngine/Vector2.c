#include "pch.h"
#include "Vector2.h"

#undef min
#undef max

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
static Vector2 smooth_damp(const Vector2* current, const Vector2* target, Vector2* current_velocity, float smooth_time, float max_speed, float delta_time);
static bool line_intersection(const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4, Vector2* result);
static bool line_segment_intersection(const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4, Vector2* result);

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
		.smooth_damp = smooth_damp,
		.line_intersection = line_intersection,
		.line_segment_intersection = line_segment_intersection
	};

	if (((char**)&static_Vector2_table)[2] == NULL) {
		Vector2 zero = Vector2_new(0, 0);
		Vector2 one = Vector2_new(1, 1);
		Vector2 up = Vector2_new(0, 1);
		Vector2 down = Vector2_new(0, -1);
		Vector2 left = Vector2_new(-1, 0);
		Vector2 right = Vector2_new(1, 0);
		Vector2 positiveInfinity;// = Vector2_new(Mathf.Infinity, Mathf.Infinity);
		Vector2 negativeInfinity;// = Vector2_new(Mathf.NegativeInfinity, Mathf.NegativeInfinity);

		OOPTool.set_const_value(&static_Vector2_table.zero, &zero, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.one, &one, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.up, &up, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.down, &down, sizeof(Vector2));
		OOPTool.set_const_value(&static_Vector2_table.left, &left, sizeof(Vector2));
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
		.f = get_impl_Vector2_table(),
		.p = p_instance
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
	return Mathf.sqrt((float)((double)self->p.x * (double)self->p.x + (double)self->p.y * (double)self->p.y));
}

static float sqr_magnitude(const Vector2* self) {
	assert(self != NULL);
	return (float)((double)self->p.x * (double)self->p.x + (double)self->p.y * (double)self->p.y);
}

static Vector2 normalized(const Vector2* self) {
	assert(self != NULL);
	Vector2 vector2 = Vector2_new(self->p.x, self->p.y);
	normalize(&vector2);
	return vector2;
}

static void normalize(Vector2* self) {
	assert(self != NULL);

	float mag = magnitude(self);
	if ((double)mag > 9.99999974737875E-06) {
		Vector2 dived = div_value(self, mag);
		OOPTool.set_const_value(self, &dived, sizeof(Vector2));
	}
	else
		OOPTool.set_const_value(self, &(get_static_Vector2_table()->zero), sizeof(Vector2));
}

static void set(Vector2* self, float x, float y) {
	assert(self != NULL);
	self->p.x = x;
	self->p.y = y;
}

static const wchar_t* to_string(const Vector2* self) {
	assert(self != NULL);
	wchar_t str[128];
	swprintf_s(str, 128, L"%f, %f", self->p.x, self->p.y);
	box_byref(wchar_t*, str, sizeof(str))
	return (const wchar_t*)str_boxed;
}

static Vector2 add(const Vector2* self, const Vector2* other) {
	assert(self != NULL);
	return Vector2_new(self->p.x + other->p.x, self->p.y + other->p.y);
}

static Vector2 sub(const Vector2* self, const Vector2* other) {
	assert(self != NULL);
	return Vector2_new(self->p.x - other->p.x, self->p.y - other->p.y);
}

static Vector2 mul(const Vector2* self, float d) {
	assert(self != NULL);
	return Vector2_new(self->p.x * d, self->p.y * d);
}

static Vector2 div_value(const Vector2* self, float d) {
	assert(self != NULL);
	return Vector2_new(self->p.x / d, self->p.y / d);
}

static bool equals(const Vector2* self, const Vector2* other) {
	assert(self != NULL);
	Vector2 subed = sub(self, other);
	return (double)sqr_magnitude(&subed) < 9.99999943962493E-11;
}

static bool not_equals(const Vector2* self, const Vector2* other) {
	assert(self != NULL); 
	Vector2 subed = sub(self, other);
	return (double)sqr_magnitude(&subed) >= 9.99999943962493E-11;
}


static Vector2 lerp(const Vector2* a, const Vector2* b, float t) {
	assert(a != NULL);
	assert(b != NULL);
	t = Mathf.clamp_01(t);
	return Vector2_new(a->p.x + (b->p.x - a->p.x) * t, a->p.y + (b->p.y - a->p.y) * t);
}

static Vector2 lerp_unclamped(const Vector2* a, const Vector2* b, float t) {
	assert(a != NULL);
	assert(b != NULL);
	return Vector2_new(a->p.x + (b->p.x - a->p.x) * t, a->p.y + (b->p.y - a->p.y) * t);
}

static Vector2 move_towards(const Vector2* current, const Vector2* target, float max_distance_delta) {
	assert(current != NULL);
	assert(target != NULL);
	Vector2 vector2 = sub(target, current);
	float mag = magnitude(&vector2);
	if ((double)mag <= (double)max_distance_delta || (double)mag == 0.0) {
		Vector2 copy_of_target = *target;
		return copy_of_target;
	}
	Vector2 div_result = div_value(&vector2, mag);
	Vector2 mul_result = mul(&div_result, max_distance_delta);
	return add(current, &mul_result);
}

static Vector2 reflect(const Vector2* in_direction, const Vector2* in_normal) {
	assert(in_direction != NULL);
	assert(in_normal != NULL);
	Vector2 mul_result = mul(in_normal, -2.f * dot(in_normal, in_direction));
	return add(&mul_result, in_direction);
}

static float dot(const Vector2* lhs, const Vector2* rhs) {
	assert(lhs != NULL);
	assert(rhs != NULL);
	return (float)((double)lhs->p.x * (double)rhs->p.x + (double)lhs->p.y * (double)rhs->p.y);
}

static float angle(const Vector2* from, const Vector2* to) {
	assert(from != NULL);
	assert(to != NULL);
	Vector2 from_normalized = normalized(from);
	Vector2 to_normalized = normalized(to);
	return Mathf.acos(Mathf.clamp(dot(&from_normalized, &to_normalized), -1.f, 1.f)) * 57.29578f;
}

static float distance(const Vector2* a, const Vector2* b) {
	assert(a != NULL);
	assert(b != NULL);
	Vector2 sub_result = sub(a, b);
	return magnitude(&sub_result);
}

static Vector2 clamp_magnitude(const Vector2* vector, float max_length) {
	assert(vector != NULL);
	if ((double)sqr_magnitude(vector) > (double)max_length * (double)max_length) {
		Vector2 vec_normalized = normalized(vector);
		return mul(&vec_normalized, max_length);
	}

	Vector2 copy = *vector;
	return copy;
}

static Vector2 min_value(const Vector2* lhs, const Vector2* rhs) {
	assert(lhs != NULL);
	assert(rhs != NULL);
	return Vector2_new(Mathf.min(lhs->p.x, rhs->p.x), Mathf.min(lhs->p.y, rhs->p.y));
}

static Vector2 max_value(const Vector2* lhs, const Vector2* rhs) {
	assert(lhs != NULL);
	assert(rhs != NULL);
	return Vector2_new(Mathf.max(lhs->p.x, rhs->p.x), Mathf.max(lhs->p.y, rhs->p.y));
}

static Vector2 smooth_damp(const Vector2* current, const Vector2* target, Vector2* current_velocity, float smooth_time, float max_speed, float delta_time) {
	assert(current != NULL);
	assert(target != NULL);
	assert(current_velocity != NULL);
	smooth_time = Mathf.max(0.0001f, smooth_time);
	float num1 = 2.f / smooth_time;
	float num2 = num1 * delta_time;
	float num3 = (float)(1.0 / (1.0 + (double)num2 + 0.479999989271164 * (double)num2 * (double)num2 + 0.234999999403954 * (double)num2 * (double)num2 * (double)num2));
	Vector2 vector = sub(current, target);
 	Vector2 vector2_1 = *target;
	float max_length = max_speed * smooth_time;
	Vector2 vector2_2 = clamp_magnitude(&vector, max_length);
	Vector2 target_a = sub(current, &vector2_2);
	Vector2 vector2_2_mul = mul(&vector2_2, num1);
	Vector2 vector2_2_add = add(current_velocity, &vector2_2_mul);
	Vector2 vector2_3 = mul(&vector2_2_add, delta_time);
	Vector2 vector2_3_mul = mul(&vector2_3, num1);
	Vector2 vector2_3_sub = sub(current_velocity, &vector2_3_mul);
	Vector2 vector2_3_result = mul(&vector2_3_sub, num3);
	OOPTool.set_const_value(current_velocity, &vector2_3_result, sizeof(Vector2));
	Vector2 vector2_4_add = add(&vector2_2, &vector2_3);
	Vector2 vector2_4_mul = mul(&vector2_4_add, num3);
	Vector2 vector2_4 = add(&target_a, &vector2_4_mul);
	Vector2 vector2_4_sub = sub(&vector2_4, &vector2_1);
	Vector2 vector2_1_sub = sub(&vector2_1, current);
	if ((double)dot(&vector2_1_sub, &vector2_4_sub) > 0.0) {
		OOPTool.set_const_value(&vector2_4, &vector2_1, sizeof(Vector2));
		Vector2 current_velocity_div = div_value(&vector2_4_sub, delta_time);
		OOPTool.set_const_value(current_velocity, &current_velocity_div, sizeof(Vector2));
	}
	return vector2_4;
}

static bool line_intersection(const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4, Vector2* result) {
	assert(p1 != NULL);
	assert(p2 != NULL);
	assert(p3 != NULL);
	assert(p4 != NULL);
	assert(result != NULL);
	float num1 = p2->f->get_x(p2) - p1->f->get_x(p1);
	float num2 = p2->f->get_y(p2) - p1->f->get_y(p1);
	float num3 = p4->f->get_x(p4) - p3->f->get_x(p3);
	float num4 = p4->f->get_y(p4) - p3->f->get_y(p3);
	float num5 = (float)((double)num1 * (double)num4 - (double)num2 * (double)num3);
	if ((double)num5 == 0.0)
		return false;
	float num6 = p3->f->get_x(p3) - p1->f->get_x(p1);
	float num7 = p3->f->get_y(p3) - p1->f->get_y(p1);
	float num8 = (float)((double)num6 * (double)num4 - (double)num7 * (double)num3) / num5;
	Vector2 resultvalue = Vector2_new(p1->f->get_x(p1) + num8 * num1, p1->f->get_y(p1) + num8 * num2);
	OOPTool.set_const_value(result, &resultvalue, sizeof(Vector2));
	return true;
}

static bool line_segment_intersection(const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4, Vector2* result) {
	assert(p1 != NULL);
	assert(p2 != NULL);
	assert(p3 != NULL);
	assert(p4 != NULL);
	assert(result != NULL);
	float num1 = p2->f->get_x(p2) - p1->f->get_x(p1);
	float num2 = p2->f->get_y(p2) - p1->f->get_y(p1);
	float num3 = p4->f->get_x(p4) - p3->f->get_x(p3);
	float num4 = p4->f->get_y(p4) - p3->f->get_y(p3);
	float num5 = (float)((double)num1 * (double)num4 - (double)num2 * (double)num3);
	if ((double)num5 == 0.0)
		return false;
	float num6 = p3->f->get_x(p3) - p1->f->get_x(p1);
	float num7 = p3->f->get_y(p3) - p1->f->get_y(p1);
	float num8 = (float)((double)num6 * (double)num4 - (double)num7 * (double)num3) / num5;
	if ((double)num8 < 0.0 || (double)num8 > 1.0)
		return false;
	float num9 = (float)((double)num6 * (double)num2 - (double)num7 * (double)num1) / num5;
	if ((double)num9 < 0.0 || (double)num9 > 1.0)
		return false;
	Vector2 resultvalue = Vector2_new(p1->f->get_x(p1) + num8 * num1, p1->f->get_y(p1) + num8 * num2);
	OOPTool.set_const_value(result, &resultvalue, sizeof(Vector2));
	return true;
}
