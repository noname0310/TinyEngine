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
	Console.write_line("%d", self->f->get_instance_id(self));
}

void listtest() {
	List_Object test = List_Object_new();
	Object O1 = Object_new(NULL, "O1", 1);
	Object O2 = Object_new(NULL, "O2", 2);
	Object O3 = Object_new(NULL, "O3", 3);
	Object O4 = Object_new(NULL, "O4", 4);
	Object O5 = Object_new(NULL, "O5", 5);
	Object O6 = Object_new(NULL, "O6", 6);
	Object O7 = Object_new(NULL, "O7", 7);
	Object O8 = Object_new(NULL, "O8", 8);
	Object O9 = Object_new(NULL, "O9", 9);
	Object O10 = Object_new(NULL, "O10", 10);

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
}

void vector2boxingtest() {
	Vector2 vector2 = Vector2_new(1, 2);
	Console.write_line("%d", vector2.f->get_x(&vector2));
	Console.write_line("%d", vector2.f->get_y(&vector2));

	box(Vector2, vector2)
	Console.write_line("%d", vector2_boxed->f->get_x(vector2_boxed));
	Console.write_line("%d", vector2_boxed->f->get_y(vector2_boxed));
}

void objecttest() {
	Object obj = Object_new(NULL, "sans sprite", 1000000000);
	Console.write_line("%s", obj.p.name);
	box(Object, obj)
	Console.write_line("%s", obj_boxed->f->get_name(obj_boxed));
	Console.write_line("%d", obj.get_type());
	Console.write_line("%d", obj_boxed->get_type());
}

void IOtest() {
	const char* a = Console.read_line();
	Console.write_line(a);
	free((char*)a);
	a = Console.read_line();
	Console.write_line(a);
	free((char*)a);

	Console.write_line_c("한글출력", ConsoleColor_white);
}

void gotest() {
	GameObject go = GameObject_new(NULL, "샌즈", 3);
	go.f->get_component(&go, get_type_Object());
	Console.write_line(go.f->get_name((Object*)&go));
	go.f->destroy((Object*)&go);
}

void ConsoleSetupTest() {
	Console.set_codepage(CodePage_Utf8);
	Console.set_size(160, 45);
}

int wmain(int argc, wchar_t* argv[]) {
	Console.write_line("=============================ConsoleSetupTest");
	ConsoleSetupTest();

	Console.write_line("=============================FontTest");
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FW_NORMAL;
	const wchar_t myFont[] = L"GulimChe";
	fontInfo.dwFontSize.X = 7;
	fontInfo.dwFontSize.Y = 14;
	memcpy(fontInfo.FaceName, myFont, sizeof(myFont));
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &fontInfo);

	Console.write_line("=============================IOtest");
	IOtest();
	Console.write_line("=============================gotest");
	gotest();
	Console.write_line("=============================listtest");
	listtest();
	Console.write_line("=============================vector2boxingtest");
	vector2boxingtest();
	Console.write_line("=============================objecttest");
	objecttest();
	Console.write_line("=============================pause");
	Console.pause();
	return 0;
}