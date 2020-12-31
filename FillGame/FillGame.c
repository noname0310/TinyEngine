#pragma comment(lib, "TinyEngine.lib")
#include "../TinyEngine/Vector2.h"
#include "../TinyEngine/Console.h"
#include "../TinyEngine/Box.h"
#include "../TinyEngine/Object.h"
#include "../TinyEngine/Interface.h"
#include "../TinyEngine/ObjectListSample.h"
#include "../TinyEngine/List.h"
#include "../TinyEngine/GameObject.h"

void printval(const Object* self) {
	Console.write_line(L"%d", self->f->get_instance_id(self));
}

void disposeObject(Object* item) {
	item->f->destroy(item);
	free(item);
}

void listtest() {
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
	test.f->for_each(&test, printval);

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
	//test.f->dispose(&test, disposeObject);
}

decl_List(int, i32)
def_List(int, i32)

void printi32val(const int self) {
	Console.write_line(L"%d", self);
}

void listtest2() {
	List_i32 Foo = List_i32_new();
	Foo.f->push_back(&Foo, 1);
	Foo.f->push_back(&Foo, 2);
	Foo.f->push_back(&Foo, 3);
	Foo.f->push_back(&Foo, 4);
	Foo.f->push_front(&Foo, 4);
	Foo.f->for_each(&Foo, printi32val);
	Foo.f->dispose(&Foo, NULL);
}

void vector2test() {
	Vector2 vec2 = Vector2_new(1, 10);
	Console.write_line(L"%f", get_static_Vector2_table()->left.f->get_x(&(get_static_Vector2_table()->left)));
}

void vector2boxingtest() {
	Vector2 vector2 = Vector2_new(1, 2);
	int a = 10;
	Console.write_line(L"%f", vector2.f->get_x(&vector2));
	Console.write_line(L"%f", vector2.f->get_y(&vector2));

	box(Vector2, vector2)
	Console.write_line(L"%f", vector2_boxed->f->get_x(vector2_boxed));
	Console.write_line(L"%f", vector2_boxed->f->get_y(vector2_boxed));
}

void objecttest() {
	Object obj = Object_new(NULL, L"sans sprite", 1000000000);
	Console.write_line(L"%s", obj.private_Object.name);
	box(Object, obj)
	Console.write_line(L"%s", obj_boxed->f->get_name(obj_boxed));
	Console.write_line(L"%d", obj.f->get_type());
	Console.write_line(L"%d", obj_boxed->f->get_type());
}

void IOtest() {
	const wchar_t* a = Console.read_line();
	Console.write_line(a);
	free((wchar_t*)a);
	a = Console.read_line();
	Console.write_line(a);
	free((wchar_t*)a);

	Console.write_line_c(L"한글출력", ConsoleColor_white);
}

void gotest() {
	GameObject go = GameObject_new(NULL, L"샌즈", 3);
	Object o = *(Object*)&go;

	go.f->get_component(&go, get_type_Object());
	Console.write_line(go.f->get_name((Object*)&go));
	go.f->destroy((Object*)&go);
}

void ConsoleSetupTest() {
	Console.default_init();
	Console.set_size(160, 45);
}

int wmain(int argc, wchar_t* argv[]) {
	Console.write_line(L"=============================ConsoleSetupTest");
	ConsoleSetupTest();

	Console.write_line(L"=============================FontTest");
	Console.write_line(L"a");
	Console.font_normalize();
	Console.write_line(L"a");

	Console.write_line(L"=============================IOtest");
	IOtest();
	Console.write_line(L"=============================gotest");
	gotest();
	Console.write_line(L"=============================listtest");
	listtest();
	Console.write_line(L"=============================listtest2");
	listtest2();
	Console.write_line(L"=============================vector2test");
	vector2test();
	Console.write_line(L"=============================vector2boxingtest");
	vector2boxingtest();
	Console.write_line(L"=============================objecttest");
	objecttest();
	Console.write_line(L"=============================pause");
	Console.pause();
	return 0;
}
