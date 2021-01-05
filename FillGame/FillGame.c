#pragma comment(lib, "TinyEngine.lib")
#include "../TinyEngine/Vector2.h"
#include "../TinyEngine/Console.h"
#include "../TinyEngine/OOPTool.h"
#include "../TinyEngine/Object.h"
#include "../TinyEngine/Interface.h"
#include "../TinyEngine/ObjectListSample.h"
#include "../TinyEngine/List.h"
#include "../TinyEngine/GameObject.h"
#include "../TinyEngine/Mathf.h"
#include "../TinyEngine/FrameBuffer.h"
#include "../TinyEngine/Graphics.h"
#include <stdlib.h>
#include <time.h>

const int width = 80;
const int height = 45;

void print_val(const Object* self) {
	Console.write_line(L"%d", self->f->get_instance_id(self));
}

void dispose_object(Object* item) {
	item->f->destroy(item);
	free(item);
}

void list_test() {
	List_Object test = List_Object_new();
	Object O1 = Object_new(NULL, L"O1", 1);
	Object O2 = Object_new(NULL, L"O2", 2);
	Object O3 = Object_new(NULL, L"O3", 3);
	Object O4 = Object_new(NULL, L"O4", 4);
	Object O5 = Object_new(NULL, L"O5", 5);
	Object O6 = Object_new(NULL, L"O6", 6);
	Object O7 = Object_new(NULL, L"O7", 7);
	Object O8 = Object_new(NULL, L"O8", 8);
	Object O9 = Object_new(NULL, L"O9", 9);
	Object O10 = Object_new(NULL, L"O10", 10);

	box(Object, O1)
	box(Object, O2)
	box(Object, O3)
	box(Object, O4)
	box(Object, O5)
	box(Object, O6)
	box(Object, O7)
	box(Object, O8)
	box(Object, O9)
	box(Object, O10)

	test.f->push_back(&test, O1_boxed);
	test.f->push_back(&test, O1_boxed);
	Node_Object* iter = test.f->push_back(&test, O1_boxed);
	test.f->push_back(&test, O1_boxed);
	test.f->push_back(&test, O1_boxed);
	test.f->push_front(&test, O3_boxed);
	test.f->insert(&test, iter, O4_boxed);
	test.f->pop_front(&test, NULL);
	test.f->pop_back(&test, NULL);
	test.f->for_each(&test, print_val);

	O1_boxed->f->destroy(O1_boxed);
	free(O1_boxed);
	O2_boxed->f->destroy(O2_boxed);
	free(O2_boxed);
	O3_boxed->f->destroy(O3_boxed);
	free(O3_boxed);
	O4_boxed->f->destroy(O4_boxed);
	free(O4_boxed);
	O5_boxed->f->destroy(O5_boxed);
	free(O5_boxed);
	O6_boxed->f->destroy(O6_boxed);
	free(O6_boxed);
	O7_boxed->f->destroy(O7_boxed);
	free(O7_boxed);
	O8_boxed->f->destroy(O8_boxed);
	free(O8_boxed);
	O9_boxed->f->destroy(O9_boxed);
	free(O9_boxed);
	O10_boxed->f->destroy(O10_boxed);
	free(O10_boxed);
	//test.f->dispose(&test, dispose_object);
}

decl_List(int, i32)
def_List(int, i32)

void print_i32_val(const int self) {
	Console.write_line(L"%d", self);
}

void list_test_2() {
	List_i32 Foo = List_i32_new();
	Foo.f->push_back(&Foo, 1);
	Foo.f->push_back(&Foo, 2);
	Foo.f->push_back(&Foo, 3);
	Foo.f->push_back(&Foo, 4);
	Foo.f->push_front(&Foo, 4);
	Foo.f->for_each(&Foo, print_i32_val);
	Foo.f->dispose(&Foo, NULL);
}

void vector2_test() {
	Vector2 vec2 = Vector2_new(1, 10);
	const wchar_t* vecstr = vec2.f->to_string(&vec2);
	Console.write_line(vecstr);
	free((void*)vecstr);

	const static_Vector2* static_Vector2 = get_static_Vector2_table();

	Console.write_line(L"%f", static_Vector2->left.f->get_x(&(static_Vector2->left)));

	const Vector2 current = Vector2_new(123.123f, 345.345f);
	const Vector2 target = Vector2_new(234.23f, 322.2f);
	Vector2 current_velocity = Vector2_new(0, 0);
	float smooth_time = 1.222f;
	float max_speed = 2.32211232f;
	float delta_time = 0.0022f;
	Vector2 smooth_damp = static_Vector2->smooth_damp(&current, &target, &current_velocity, smooth_time, max_speed, delta_time);
	const wchar_t* smooth_dampstr = smooth_damp.f->to_string(&smooth_damp);
	const wchar_t* current_velocitystr = current_velocity.f->to_string(&current_velocity);
	Console.write_line(L"static_Vector2->smooth_damp: [%s] [%s]", smooth_dampstr, current_velocitystr);
	free((void*)current_velocitystr);
	free((void*)smooth_dampstr);
}

void vector2_boxing_test() {
	Vector2 vector2 = Vector2_new(1, 2);
	int a = 10;
	Console.write_line(L"%f", vector2.f->get_x(&vector2));
	Console.write_line(L"%f", vector2.f->get_y(&vector2));

	box(Vector2, vector2)
	Console.write_line(L"%f", vector2_boxed->f->get_x(vector2_boxed));
	Console.write_line(L"%f", vector2_boxed->f->get_y(vector2_boxed));
}

void object_test() {
	Object obj = Object_new(NULL, L"sans sprite", 1000000000);
	Console.write_line(L"%s", obj.private_Object.name);
	box(Object, obj)
	Console.write_line(L"%s", obj_boxed->f->get_name(obj_boxed));
	Console.write_line(L"%d", obj.f->get_type());
	Console.write_line(L"%d", obj_boxed->f->get_type());
}

void io_test() {
	const wchar_t* a = Console.read_line();
	Console.write_line(a);
	free((wchar_t*)a);
	a = Console.read_line();
	Console.write_line(a);
	free((wchar_t*)a);

	Console.write_line_c(L"한글출력", ConsoleColor_white);
}

void go_test() {
	GameObject go = GameObject_new(NULL, L"샌즈", 3);
	//Object o = *(Object*)&go;

	go.f->get_component(&go, get_type_Object());
	Console.write_line(go.f->get_name((Object*)&go));
	go.f->destroy((Object*)&go);
}

void console_setup_test() {
	Console.default_init();
	Console.set_size(width, height);
}

void font_test() {
	Console.write_line(L"a");
	Console.font_normalize();
	Console.write_line(L"a");
}

void mathf_test() {
	/*Console.write_line(L"Mathf.PI: %f", Mathf.PI);
	Console.write_line(L"Mathf.Infinity: %f", Mathf.Infinity);
	Console.write_line(L"Mathf.NegativeInfinity: %f", Mathf.NegativeInfinity);
	Console.write_line(L"Mathf.Deg2Rad: %f", Mathf.Deg2Rad);
	Console.write_line(L"Mathf.Rad2Deg: %f", Mathf.Rad2Deg);*/
	/*for (int i = -10; i < 10; i++)
	{
		if (Mathf.sin(i) != sinf(i)) {
			Console.write_line(L"Mathf.sin(%d): %f", i, Mathf.sin(i));
			Console.write_line(L"sinf(%d):      %f", i, sinf(i));
		}
	}
	for (int i = -10; i < 10; i++)
	{
		if (Mathf.cos(i) != cosf(i)) {
			Console.write_line(L"Mathf.cos(%d): %f", i, Mathf.cos(i));
			Console.write_line(L"cosf(%d):      %f", i, cosf(i));
		}
	}
	for (int i = -10; i < 10; i++)
	{
		if (Mathf.tan(i) != tanf(i)) {
			Console.write_line(L"Mathf.tan(%d): %f", i, Mathf.tan(i));
			Console.write_line(L"tanf(%d):      %f", i, tanf(i));
		}
	}*/
	/*for (float i = -1; i < 1; i+= 0.1)
	{
		if (Mathf.asin(i) != asinf(i)) {
			Console.write_line(L"Mathf.asin(%f): %f", i, Mathf.asin(i));
			Console.write_line(L"asinf(%f):      %f", i, asinf(i));
		}
	}
	for (float i = -1; i < 1; i += 0.1)
	{
		if (Mathf.acos(i) != acosf(i)) {
			Console.write_line(L"Mathf.acos(%f): %f", i, Mathf.acos(i));
			Console.write_line(L"acosf(%f):      %f", i, acosf(i));
		}
	}*/
	/*for (float i = -2; i < 2; i += 0.1f)
	{
		if (Mathf.atan(i) != atanf(i)) {
			Console.write_line(L"Mathf.atan(%f): %f", i, Mathf.atan(i));
			Console.write_line(L"atanf(%f):      %f", i, atanf(i));
		}
	}*/
	/*for (float i = -1; i < 1; i += 0.1f)
	{
		if (Mathf.atan2(i, 1) != atan2f(i, 1)) {
			Console.write_line(L"Mathf.atan2(%f): %f", i, Mathf.atan2(i, 1));
			Console.write_line(L"atan2f(%f):      %f", i, atan2f(i, 1));
		}
	}*/
	/*for (int i = -10; i < 10; i++)
	{
		if (Mathf.sqrt(i) != sqrtf(i)) {
			Console.write_line(L"Mathf.sqrt(%d): %f", i, Mathf.sqrt(i));
			Console.write_line(L"sqrtf(%d):      %f", i, sqrtf(i));
		}
	}*/
	/*for (int i = -10; i < 10; i++)
	{
		if (Mathf.ldexpf(i, 10) != ldexpf(i, 10)) {
			Console.write_line(L"Mathf.ldexpf(%d): %f", i, Mathf.ldexpf(i, 10));
			Console.write_line(L"ldexpf(%d):       %f", i, ldexpf(i, 10));
		}
	}*/
	/*for (int i = -10; i < 10; i += 100)
	{
		Console.write_line(L"Mathf.closest_power_of_two(%d): %d", i, Mathf.closest_power_of_two(i));
	}*/
	/*Console.write_line(L"Mathf.abs(-190.232f  %f): %f", -190.232f, Mathf.abs(-190.232f));
	Console.write_line(L"Mathf.abs(190.353f   %f): %f", 190.353f, Mathf.abs(190.353f));
	Console.write_line(L"Mathf.abs_i32(-190): %d", Mathf.abs_i32(-190));
	Console.write_line(L"Mathf.abs_i32(190): %d", Mathf.abs_i32(190));
	Vector2 a = Vector2_new(1.123f, 2);
	Vector2 b = Vector2_new(3, 4.234f);
	Vector2 c = Vector2_new(5, 6);
	Vector2 d = Vector2_new(7.123123f, 8);
	Vector2 result = Vector2_new(2, 2);
	get_static_Vector2_table()->line_intersection(&a, &b, &c, &d, &result);
	Console.write_line(L"%f %f", result.f->get_x(&result), result.f->get_y(&result));*/
	/*for (float i = -1; i < 1; i += 0.1f)
	{
		Console.write_line(L"Mathf.gamma_to_linear_space(%f): %f", i, Mathf.gamma_to_linear_space(i));
	}
	for (float i = -1; i < 1; i += 0.1f)
	{
		Console.write_line(L"Mathf.linear_to_gamma_space(%f): %f", i, Mathf.linear_to_gamma_space(i));
	}*/
	/*for (float i = -1; i < 1; i += 0.1f)
	{
		Console.write_line(L"Mathf.pow(2, %f): %f", i, Mathf.pow(2, i));
		Console.write_line(L"pow(2, %f):       %f", i, pow(2, i));
	}*/
	/*for (float i = -1; i < 1; i += 0.1f)
	{
		Console.write_line(L"Mathf.exp(%f): %f", i, Mathf.exp(i));
		Console.write_line(L"exp(%f):       %f", i, exp(i));
	}*/
	/*for (float i = -1; i < 1; i += 0.1f)
	{
		Console.write_line(L"Mathf.log_e(%f): %f", i, Mathf.log_e(i));
		Console.write_line(L"logf(%f):        %f", i, logf(i));
	}
	for (float i = -1; i < 1; i += 0.1f)
	{
		Console.write_line(L"Mathf.log_10(%f): %f", i, Mathf.log_10(i));
		Console.write_line(L"log10f(%f):       %f", i, log10f(i));
	}*/
	/*for (float i = -1; i < 1; i += 0.001f)
	{
		Console.write_line(L"Mathf.log(10, %f): %f", i, Mathf.log(10, i));
	}*/
	/*Console.write_line(L"%f", 0.214);
	Console.write_line(L"%f", Mathf.half_to_float(Mathf.float_to_half(0.214)));
	Console.write_line(L"%f", Mathf.ceil(4.214f));
	Console.write_line(L"%f", Mathf.floor(4.214f));
	Console.write_line(L"%f", Mathf.round(4.214f));*/
	/*Console.write_line(L"%d", Mathf.floor_to_int(10.0f));
	Console.write_line(L"%d", Mathf.floor_to_int(10.2f));
	Console.write_line(L"%d", Mathf.floor_to_int(10.7f));
	Console.write_line(L"%d", Mathf.floor_to_int(-10.0f));
	Console.write_line(L"%d", Mathf.floor_to_int(-10.2f));
	Console.write_line(L"%d", Mathf.floor_to_int(-10.7f));*/
	/*Console.write_line(L"%d", Mathf.round_to_int(10.0f));
	Console.write_line(L"%d", Mathf.round_to_int(10.2f));
	Console.write_line(L"%d", Mathf.round_to_int(10.7f));
	Console.write_line(L"%d", Mathf.round_to_int(-10.0f));
	Console.write_line(L"%d", Mathf.round_to_int(-10.2f));
	Console.write_line(L"%d", Mathf.round_to_int(-10.7f));*/

    Console.write_line(L"%d", Mathf.ceil_to_int(10.0f));
	Console.write_line(L"%d", Mathf.ceil_to_int(10.2f));
	Console.write_line(L"%d", Mathf.ceil_to_int(10.7f));
	Console.write_line(L"%d", Mathf.ceil_to_int(-10.0f));
	Console.write_line(L"%d", Mathf.ceil_to_int(-10.2f));
	Console.write_line(L"%d", Mathf.ceil_to_int(-10.7f));
}

void buffer_foreach_item(Point index, wchar_t* item) {
	if (rand() % 100 == 0)
		*item = L'*';
	else
		*item = L' ';
}

void buffer_foreach_item1(Point index, wchar_t* item) {
	*item = L' ';
}

void buffer_foreach_item2(Point index, wchar_t* item) {
	if (!(index.y % 20 && index.x % 20))
		*item = L'*';
	else
		*item = L' ';
}

static float y = 0;

void buffer_foreach_item3(Point index, wchar_t* item) {
	*item = L"    !*#$@"[(int)(Mathf.perlin_noise(index.x, index.y + y, 0.03, 10, 0) * 9) % 10];
}

void frame_buffer_test() {
	Console.set_cursor_vis(CursorStat_hide);
	FrameBuffer framebuffer = FrameBuffer_new(width, height);
	for (size_t i = 0; i < 5000; i++)
	{
		framebuffer.f->for_each(&framebuffer, buffer_foreach_item2);
		framebuffer.f->print(&framebuffer);
		framebuffer.f->for_each(&framebuffer, buffer_foreach_item);
		framebuffer.f->print(&framebuffer);
	}
	framebuffer.f->dispose(&framebuffer);
}

void graphics_test() {
	Console.set_cursor_vis(CursorStat_hide);
	Graphics graphics = Graphics_new(width, height);
	for (size_t i = 0; i < 5000; i++)
	{
		/*graphics.f->for_each((const FrameBuffer*)&graphics, buffer_foreach_item2);
		graphics.f->print((FrameBuffer*)&graphics);
		graphics.f->for_each((const FrameBuffer*)&graphics, buffer_foreach_item);
		graphics.f->print((FrameBuffer*)&graphics);*/
		graphics.f->for_each((const FrameBuffer*)&graphics, buffer_foreach_item3);
		graphics.f->print((FrameBuffer*)&graphics);
		y += 1;
	}
	graphics.f->dispose((FrameBuffer*)&graphics);
}

int wmain(int argc, wchar_t* argv[]) {
	Console.write_line(L"=============================ConsoleSetupTest");
	console_setup_test();
	Console.write_line(L"=============================FontTest");
	font_test();
	//Console.write_line(L"=============================IOtest");
	//io_test();
	Console.write_line(L"=============================gotest");
	go_test();
	Console.write_line(L"=============================listtest");
	list_test();
	Console.write_line(L"=============================listtest2");
	list_test_2();
	Console.write_line(L"=============================vector2test");
	vector2_test();
	Console.write_line(L"=============================vector2boxingtest");
	vector2_boxing_test();
	Console.write_line(L"=============================objecttest");
	object_test();
	//Console.write_line(L"=============================framebuffertest");
	//frame_buffer_test();
	Console.write_line(L"=============================graphics_test");
	graphics_test();
	//Console.write_line(L"=============================mathf_test");
	//mathf_test();
	Console.write_line(L"=============================Pause");
	Console.pause();
	return 0;
}
