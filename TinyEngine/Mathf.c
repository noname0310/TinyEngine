#include "pch.h"
#include "Mathf.h"

static float sin (float f);
static float cos (float f);
static float tan (float f);
static float asin (float f);
static float acos (float f);
static float atan (float f);
static float atan2 (float y, float x);
static float sqrt (float f);
static float abs_value (float f);
static int abs_i32 (int f);
static float min_value(float a, float b);
static float min_args(int count, ...);
static int min_i32(int a, int b);
static int min_i32_args(int count, ...);
static float max_value(float a, float b);
static float max_args(int count, ...);
static int max_i32(int a, int b);
static int max_i32_args(int count, ...);
static float pow (float f, float p);
static float exp (float power);
static float log (float f, float p);
static float log_e (float f);
static float log_10 (float f);
static float ceil (float f);
static float floor (float f);
static float round (float f);
static int ceil_to_int (float f);
static int floor_to_int (float f);
static int round_to_int (float f);
static float sign (float f);
static float clamp (float value, float min, float max);
static int clamp_i32 (int value, int min, int max);
static float clamp_01 (float value);
static float lerp (float a, float b, float t);
static float lerp_unclamped (float a, float b, float t);
static float lerp_angle (float a, float b, float t);
static float move_towards (float current, float target, float max_delta);
static float move_towards_angle (float current, float target, float max_delta);
static float smooth_step (float from, float to, float t);
static float gamma (float value, float absmax, float gamma);
static bool approximately (float a, float b);
static float smooth_damp (float current, float target, float* current_velocity, float smooth_time, float max_speed, float delta_time);
static float smooth_damp_angle (float current, float target, float* current_velocity, float smooth_time, float max_speed, float delta_time);
static float repeat (float t, float length);
static float ping_pong (float t, float length);
static float inverse_lerp (float a, float b, float value);
static int closest_power_of_two (int value);
static float gamma_to_linear_space (float value);
static float linear_to_gamma_space (float value);
static bool is_power_of_two (int value);
static int next_power_of_two (int value);
static float delta_angle (float current, float target);
static float perlin_noise (float x, float y);
static bool line_intersection (const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4, Vector2* result);
static bool line_segment_intersection (const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4, Vector2* result);
static unsigned short float_to_half (float value);
static float half_to_float (unsigned short value);

static float frexpf(float, int*);
static float ldexpf(float, int);

//https://github.com/jeremybarnes/cephes/blob/master/single/sinf.c

const static float MAXNUMF = 3.4028234663852885981170418348451692544e38f;
const static float FOPI = 1.27323954473516f;
const static float PIF = 3.14159265358979323846264338328f;
const static float PIO2F = 1.57079632679489661923132169164f;
const static float PIO4F = 0.78539816339744830961566084582f;

const static float DP1 = 0.78515625f;
const static float DP2 = 2.4187564849853515625e-4f;
const static float DP3 = 3.77489497744594108e-8f;
const static float lossth = 8192.f;
const static float T24M1 = 16777215.f;

const static float NAN = (float)(((float)(1e+300 * 1e+300)) * 0.0F);

const static float sincof[] = {
-1.9515295891E-4f,
 8.3321608736E-3f,
-1.6666654611E-1f
};

const static float coscof[] = {
 2.443315711809948E-005f,
-1.388731625493765E-003f,
 4.166664568298827E-002f
};

const _Mathf Mathf = {
	.Epsilon = 1.401298E-45f,
	.PI = 3.141593f,
	.Infinity = ((float)(1e+300 * 1e+300)),
	.NegativeInfinity = -((float)(1e+300 * 1e+300)),
	.Deg2Rad = 0.01745329f,
	.Rad2Deg = 57.29578f,
	.sin = sin,
	.cos = cos,
	.tan = tan,
	.asin = asin,
	.acos = acos,
	.atan = atan,
	.atan2 = atan2,
	.sqrt = sqrt,
	.abs = abs_value,
	.abs_i32 = abs_i32,
	.min = min_value,
	.min_args = min_args,
	.min_i32 = min_i32,
	.min_i32_args = min_i32_args,
	.max = max_value,
	.max_args = max_args,
	.max_i32 = max_i32,
	.max_i32_args = max_i32_args,
	.pow = pow,
	.exp = exp,
	.log = log,
	.log_e = log_e,
	.log_10 = log_10,
	.ceil = ceil,
	.floor = floor,
	.round = round,
	.ceil_to_int = ceil_to_int,
	.floor_to_int = floor_to_int,
	.round_to_int = round_to_int,
	.sign = sign,
	.clamp = clamp,
	.clamp_i32 = clamp_i32,
	.clamp_01 = clamp_01,
	.lerp = lerp,
	.lerp_unclamped = lerp_unclamped,
	.lerp_angle = lerp_angle,
	.move_towards = move_towards,
	.move_towards_angle = move_towards_angle,
	.smooth_step = smooth_step,
	.gamma = gamma,
	.approximately = approximately,
	.smooth_damp = smooth_damp,
	.smooth_damp_angle = smooth_damp_angle,
	.repeat = repeat,
	.ping_pong = ping_pong,
	.inverse_lerp = inverse_lerp,
	.closest_power_of_two = closest_power_of_two,
	.gamma_to_linear_space = gamma_to_linear_space,
	.linear_to_gamma_space = linear_to_gamma_space,
	.is_power_of_two = is_power_of_two,
	.next_power_of_two = next_power_of_two,
	.delta_angle = delta_angle,
	.perlin_noise = perlin_noise,
	.line_intersection = line_intersection,
	.line_segment_intersection = line_segment_intersection,
	.float_to_half = float_to_half,
	.half_to_float = half_to_float
};

#pragma warning(disable:4244)
static float sin(float f) {
	const float* p;
	float x, y, z;
	register unsigned long j;
	register int sign;

	sign = 1;
	x = f;
	if (f < 0) {
		sign = -1;
		x = -f;
	}
	if (x > T24M1) {
		return 0.0;
	}
	j = FOPI * x;
	y = j;
	if (j & 1) {
		j += 1;
		y += 1.0;
	}
	j &= 7;
	if (j > 3) {
		sign = -sign;
		j -= 4;
	}

	if (x > lossth) {
		x = x - y * PIO4F;
	}
	else {
		x = ((x - y * DP1) - y * DP2) - y * DP3;
	}

	z = x * x;
	if ((j == 1) || (j == 2)) {
		p = coscof;
		y = *p++;
		y = y * z + *p++;
		y = y * z + *p++;
		y *= z * z;
		y -= 0.5 * z;
		y += 1.0;
	}
	else {
		p = sincof;
		y = *p++;
		y = y * z + *p++;
		y = y * z + *p++;
		y *= z * x;
		y += x;
	}
	if (sign < 0)
		y = -y;
	return y;
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float cos(float f) {
	float x, y, z;
	int j, sign;

	sign = 1;
	x = f;
	if (x < 0)
		x = -x;

	if (x > T24M1)
		return 0.0;

	j = FOPI * x;
	y = j;
	if (j & 1) {
		j += 1;
		y += 1.0;
	}
	j &= 7;
	if (j > 3) {
		j -= 4;
		sign = -sign;
	}

	if (j > 1)
		sign = -sign;

	if (x > lossth) {
		x = x - y * PIO4F;
	}
	else
		x = ((x - y * DP1) - y * DP2) - y * DP3;

	z = x * x;

	if ((j == 1) || (j == 2)) {
		y = (((-1.9515295891E-4 * z
			+ 8.3321608736E-3) * z
			- 1.6666654611E-1) * z * x)
			+ x;
	}
	else {
		y = ((2.443315711809948E-005 * z
			- 1.388731625493765E-003) * z
			+ 4.166664568298827E-002) * z * z;
		y -= 0.5 * z;
		y += 1.0;
	}
	if (sign < 0)
		y = -y;
	return y;
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float tan(float f) {
	float x, y, z, zz;
	long j;
	int sign;

	if (f < 0.0) {
		x = -f;
		sign = -1;
	}
	else {
		x = f;
		sign = 1;
	}

	if (x > lossth) {
		return 0.0;
	}

	j = FOPI * x;
	y = j;

	if (j & 1) {
		j += 1;
		y += 1.0;
	}

	z = ((x - y * DP1) - y * DP2) - y * DP3;
	zz = z * z;

	if (x > 1.0e-4) {
		y =
			(((((9.38540185543E-3 * zz
				+ 3.11992232697E-3) * zz
				+ 2.44301354525E-2) * zz
				+ 5.34112807005E-2) * zz
				+ 1.33387994085E-1) * zz
				+ 3.33331568548E-1) * zz * z
			+ z;
	}
	else
		y = z;

	if (j & 2)
		y = -1.0 / y;

	if (sign < 0)
		y = -y;

	return y;
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float asin(float f) {
	if (f < -1 || 1 < f)
		assert(!"f must be between -1 and 1.");

	float a, x, z;
	int sign, flag;

	x = f;

	if (x > 0) {
		sign = 1;
		a = x;
	}
	else {
		sign = -1;
		a = -x;
	}

	if (a > 1.0)
		return 0.0;

	if (a < 1.0e-4) {
		z = a;
		goto done;
	}

	if (a > 0.5) {
		z = 0.5 * (1.0 - a);
		x = sqrt(z);
		flag = 1;
	}
	else {
		x = a;
		z = x * x;
		flag = 0;
	}

	z =
		((((4.2163199048E-2 * z
			+ 2.4181311049E-2) * z
			+ 4.5470025998E-2) * z
			+ 7.4953002686E-2) * z
			+ 1.6666752422E-1) * z * x
		+ x;

	if (flag != 0) {
		z = z + z;
		z = PIO2F - z;
	}
done:
	if (sign < 0)
		z = -z;
	return z;
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float acos(float f) {
	if (f < -1 || 1 < f) {
		assert(!"f must be between -1 and 1.");
	}
	if (f < -1.0)
		goto domerr;

	if (f < -0.5)
		return PIF - 2.0 * asin(sqrt(0.5 * (1.0 + f)));

	if (f > 1.0) {
	domerr:
		return 0.0;
	}

	if (f > 0.5)
		return 2.0 * asin(sqrt(0.5 * (1.0 - f)));

	return PIO2F - asin(f);
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float atan(float f) {
	float x, y, z;
	int sign;

	x = f;

	if (f < 0.0) {
		sign = -1;
		x = -f;
	}
	else {
		sign = 1;
		x = f;
	}

	if (x > 2.414213562373095) {
		y = PIO2F;
		x = -(1.0 / x);
	}

	else if (x > 0.4142135623730950) {
		y = PIO4F;
		x = (x - 1.0) / (x + 1.0);
	}
	else
		y = 0.0;

	z = x * x;
	y +=
		(((8.05374449538e-2 * z
			- 1.38776856032E-1) * z
			+ 1.99777106478E-1) * z
			- 3.33329491539E-1) * z * x
		+ x;

	if (sign < 0)
		y = -y;

	return y;
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float atan2(float y, float x) {
	float z, w;
	int code;

	code = 0;

	if (x < 0.0)
		code = 2;
	if (y < 0.0)
		code |= 1;

	if (x == 0.0) {
		if (code & 1) {
			return -PIO2F;
			//return(3.0 * PIO2F);
		}
		if (y == 0.0)
			return 0.0;
		return PIO2F;
	}

	if (y == 0.0) {
		if (code & 2)
			return PIF;
		return 0.0;
	}

	switch (code) {
		default:
		case 0:
		case 1: w = 0.0; break;
		case 2: w = PIF; break;
		case 3: w = -PIF; break;
		/*case 0: w = 0.0; break;
		case 1: w = 2.0 * PIF; break;
		case 2:
		case 3: w = PIF; break;*/
	}

	z = atan(y / x);

	return w + z;
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float frexpf(float x, int* pw2) {
	union {
		float y;
		unsigned short i[2];
	} u;
	int i, k;
	short* q;

	u.y = x;

	q = &u.i[1];

	i = (*q >> 7) & 0xff;
	if (i == 0) {
		if (u.y == 0.0) {
			*pw2 = 0;
			return 0.0;
		}
		do {
			u.y *= 2.0;
			i -= 1;
			k = (*q >> 7) & 0xff;
		} while (k == 0);
		i = i + k;
	}
	i -= 0x7e;
	*pw2 = i;
	*q &= 0x807f;
	*q |= 0x3f00;
	return u.y;
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float ldexpf(float x, int pw2) {
	union {
		float f;
		long l;
	} fl;
	long e;

	fl.f = x;

	e = (fl.l >> 23) & 0x000000ff;
	e += pw2;
	fl.l = ((e & 0xff) << 23) | (fl.l & 0x807fffff);

	return(fl.f);
}
#pragma warning(default:4244)

#pragma warning(disable:4244)
static float sqrt(float f)
{
	if (f < 0)
		return NAN;

	float x, y;
	int e;
	if (f <= 0.0)
		return 0.0;

	x = frexpf(f, &e);
	if (e & 1) {
		x = x + x;
		e -= 1;
	}

	e >>= 1;

	if (x > 1.41421356237) {
		x = x - 2.0;
		y =
			(((((-9.8843065718E-4 * x
				+ 7.9479950957E-4) * x
				- 3.5890535377E-3) * x
				+ 1.1028809744E-2) * x
				- 4.4195203560E-2) * x
				+ 3.5355338194E-1) * x
			+ 1.41421356237E0;
		goto sqdon;
	}

	if (x > 0.707106781187) {
		x = x - 1.0;
		y =
			(((((1.35199291026E-2 * x
				- 2.26657767832E-2) * x
				+ 2.78720776889E-2) * x
				- 3.89582788321E-2) * x
				+ 6.24811144548E-2) * x
				- 1.25001503933E-1) * x * x
			+ 0.5 * x
			+ 1.0;
		goto sqdon;
	}

	x = x - 0.5;
	y =
		(((((-3.9495006054E-1 * x
			+ 5.1743034569E-1) * x
			- 4.3214437330E-1) * x
			+ 3.5310730460E-1) * x
			- 3.5354581892E-1) * x
			+ 7.0710676017E-1) * x
		+ 7.07106781187E-1;

sqdon:
	y = ldexpf(y, e);
	return y;
}
#pragma warning(default:4244)

static float abs_value(float f) {

}

static int abs_i32(int f) {
	int s = f >> 31;
	return (f ^ s) - s;
}

static float min_value(float a, float b) {
    return min(a, b);
}

static float min_args(int count, ...) {
    va_list args;
    va_start(args, count);

    float min = va_arg(args, float);
    for (int i = 0; i < count - 1; ++i) {
        float next = va_arg(args, float);
        min = min < next ? min : next;
    }
    va_end(args);

    return min;
}

static int min_i32(int a, int b) {
    return min(a, b);
}

static int min_i32_args(int count, ...) {
    va_list args;
    va_start(args, count);

    int min = va_arg(args, int);
    for (int i = 0; i < count - 1; ++i) {
        int next = va_arg(args, int);
        min = min < next ? min : next;
    }
    va_end(args);

    return min;
}

static float max_value(float a, float b) {
    return max(a, b);
}

static float max_args(int count, ...) {
    va_list args;
    va_start(args, count);

    float max = va_arg(args, float);
    for (int i = 0; i < count - 1; ++i) {
        float next = va_arg(args, float);
        max = max < next ? next : max;
    }
    va_end(args);

    return max;
}

static int max_i32(int a, int b) {
    return max(a, b);
}

static int max_i32_args(int count, ...) {
    va_list args;
    va_start(args, count);

    int max = va_arg(args, int);
    for (int i = 0; i < count - 1; ++i) {
        int next = va_arg(args, int);
        max = max < next ? next : max;
    }
    va_end(args);

    return max;
}

static float pow(float f, float p) {

}

static float exp(float power) {

}

static float log(float f, float p) {

}

static float log_e(float f) {

}

static float log_10(float f) {

}

static float ceil(float f) {

}

static float floor(float f) {

}

static float round(float f) {

}

static int ceil_to_int(float f) {

}

static int floor_to_int(float f) {

}

static int round_to_int(float f) {

}

static float sign(float f) {
	return ((double)f >= 0.0) ? 1.f : -1.f;
}

static float clamp(float value, float min, float max) {
	if ((double)value < (double)min)
		value = min;
	else if ((double)value > (double)max)
		value = max;
	return value;
}

static int clamp_i32(int value, int min, int max) {
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
	return value;
}

static float clamp_01(float value) {
	if ((double)value < 0.0)
		return 0.0f;
	if ((double)value > 1.0)
		return 1;
	return value;
}

static float lerp(float a, float b, float t) {
	return a + (b - a) * clamp_01(t);
}

static float lerp_unclamped(float a, float b, float t) {
	return a + (b - a) * t;
}

static float lerp_angle(float a, float b, float t) {
	float num = repeat(b - a, 360);
	if ((double)num > 180.0)
		num -= 360;
	return a + num * clamp_01(t);
}

static float move_towards(float current, float target, float max_delta) {
	if ((double)abs_value(target - current) <= (double)max_delta)
		return target;
	return current + sign(target - current) * max_delta;
}

static float move_towards_angle(float current, float target, float max_delta) {
	target = current + delta_angle(current, target);
	return move_towards(current, target, max_delta);
}

static float smooth_step(float from, float to, float t) {
	t = clamp_01(t);
	t = (float)(-2.0 * (double)t * (double)t * (double)t + 3.0 * (double)t * (double)t);
	return (float)((double)to * (double)t + (double)from * (1.0 - (double)t));
}

static float gamma(float value, float absmax, float gamma) {
	bool flag = false;
	if ((double)value < 0.0)
		flag = true;
	float num1 = abs_value(value);
	if ((double)num1 > (double)absmax)
	{
		if (flag)
			return -num1;
		return num1;
	}
	float num2 = pow(num1 / absmax, gamma) * absmax;
	if (flag)
		return -num2;
	return num2;
}

static bool approximately(float a, float b) {
	return (double)abs_value(b - a) < (double)max_value(1E-06f * max_value(abs_value(a), abs_value(b)), Mathf.Epsilon * 8);
}

static float smooth_damp(float current, float target, float* current_velocity, float smooth_time, float max_speed, float delta_time) {
	smooth_time = max_value(0.0001f, smooth_time);
	float num1 = 2 / smooth_time;
	float num2 = num1 * delta_time;
	float num3 = (float)(1.0 / (1.0 + (double)num2 + 0.479999989271164 * (double)num2 * (double)num2 + 0.234999999403954 * (double)num2 * (double)num2 * (double)num2));
	float num4 = current - target;
	float num5 = target;
	float max = max_speed * smooth_time;
	float num6 = clamp(num4, -max, max);
	target = current - num6;
	float num7 = (*current_velocity + num1 * num6) * delta_time;
	*current_velocity = (*current_velocity - num1 * num7) * num3;
	float num8 = target + (num6 + num7) * num3;
	if ((double)num5 - (double)current > 0.0 == (double)num8 > (double)num5)
	{
		num8 = num5;
		*current_velocity = (num8 - num5) / delta_time;
	}
	return num8;
}

static float smooth_damp_angle(float current, float target, float* current_velocity, float smooth_time, float max_speed, float delta_time) {
	target = current + delta_angle(current, target);
	return smooth_damp(current, target, current_velocity, smooth_time, max_speed, delta_time);
}

static float repeat(float t, float length) {
	return t - floor(t / length) * length;
}

static float ping_pong(float t, float length) {
	t = repeat(t, length * 2);
	return length - abs_value(t - length);
}

static float inverse_lerp(float a, float b, float value) {
	if ((double)a != (double)b)
		return clamp_01((float)(((double)value - (double)a) / ((double)b - (double)a)));
	return 0.0f;
}

static int closest_power_of_two(int value) {

}

static float gamma_to_linear_space(float value) {

}

static float linear_to_gamma_space(float value) {

}

static bool is_power_of_two(int value) {

}

static int next_power_of_two(int value) {

}

static float delta_angle(float current, float target) {
	float num = repeat(target - current, 360);
	if ((double)num > 180.0)
		num -= 360;
	return num;
}

static float perlin_noise(float x, float y) {

}

static bool line_intersection(const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4, Vector2* result) {
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

static unsigned short float_to_half(float value) {

}

static float half_to_float(unsigned short value) {

}
