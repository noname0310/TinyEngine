#pragma comment(lib, "TinyEngine.lib")
#include "../TinyEngine/Vector2.h"
#include "../TinyEngine/Console.h"
#include "../TinyEngine/Box.h"
#include "../TinyEngine/Object.h"
#include "../TinyEngine/Interface.h"
#include "../TinyEngine/ObjectListSample.h"
#include "../TinyEngine/List.h"

void printval(Object* self) {
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

int main() {
	objecttest();
	return 0;
}