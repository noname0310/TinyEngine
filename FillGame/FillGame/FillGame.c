#pragma comment(lib, "TinyEngine.lib")
#include "../TinyEngine/Vector2.h"
#include "../TinyEngine/Console.h"
#include "../TinyEngine/TinyEngine.h"
#include "../TinyEngine/Box.h"

int main() {
	Vector2 vector2 = Vector2_new(1, 2);
	
	Console.write_line("%d", vector2.f->get_x(&vector2));
	Console.write_line("%d", vector2.f->get_y(&vector2));

	box(Vector2, vector2);
	Console.write_line("%d", vector2_boxed->f->get_y(&vector2));
	return 0;
}