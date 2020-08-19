#pragma comment(lib, "TinyEngine.lib")
#include "../TinyEngine/Vector2.h"
#include "../TinyEngine/Console.h"
#include "../TinyEngine/Box.h"
#include "../TinyEngine/Object.h"
#include "../TinyEngine/Interface.h"

int main() {
	Vector2 vector2 = Vector2_new(1, 2);
	Console.write_line("%d", vector2.f->get_x(&vector2));
	Console.write_line("%d", vector2.f->get_y(&vector2));

	box(Vector2, vector2)
	Console.write_line("%d", vector2_boxed->f->get_x(vector2_boxed));
	Console.write_line("%d", vector2_boxed->f->get_y(vector2_boxed));

	Object obj = Object_new("sans sprite", 1000000000);
	Console.write_line("%s", obj.p.name);
	box(Object, obj)
	Console.write_line("%s", obj_boxed->f->get_name(obj_boxed));
	Console.write_line("%d", obj.get_type());
	Console.write_line("%d", obj_boxed->get_type());
	return 0;
}