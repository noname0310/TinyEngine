#pragma comment(lib, "TinyEngine.lib")
#include "../TinyEngine/Vector2.h"
#include "../TinyEngine/Console.h"
#include "../TinyEngine/TinyEngine.h"

int main() {
	Vector2 vector2 = Vector2_new(1, 2);
	Console.write_line("%d", vector2.f->get_x(&vector2));
	Console.write_line("%d", vector2.f->get_y(&vector2));
	Console.write_line("Ssa");
	Console.write_line("asdaas%d", 1);
	return 0;
}