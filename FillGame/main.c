#include <stdio.h>
#include <Vector2.h>

int main() {
	Vector2 vector2 = Vector2_new(1, 2);
	printf("%d ", vector2.f->get_x(&vector2));
	printf("%d", vector2.f->get_y(&vector2));
	return 0;
}