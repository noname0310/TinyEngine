#include "Console.h"
def_Option(Keys);

static void Console_write_line(const char* str);
static void Console_write(const char* str);
static void Console_write_line_c(const char* str, ConsoleColor color);
static void Console_write_c(const char* str, ConsoleColor color);

static bool Console_has_input(void);
static Option_Keys Console_read_key(void);

static void Console_set_cursor_vis(CursorStat stat);
static void Console_set_pos(int x, int y);
static void Console_set_color(ConsoleColor color);
static void Console_set_size(int x, int y);
static void Console_set_title(const char* title);
static void Console_clear(void);

struct _Console Console = {
	.write_line = Console_write_line,
	.write = Console_write,
	.write_line_c = Console_write_line_c,
	.write_c = Console_write_c,

	.has_input = Console_has_input,
	.read_key = Console_read_key,

	.set_cursor_vis = Console_set_cursor_vis,
	.set_pos = Console_set_pos,
	.set_color = Console_set_color,
	.set_size = Console_set_size,
	.set_title = Console_set_title,
	.clear = Console_clear
};

static void Console_write_line(const char* str) {
	printf_s("%s\n", str);
}

static void Console_write(const char* str) {
	printf_s(str);
}

static void Console_write_line_c(const char* str, ConsoleColor color) {
	Console_set_color(color);
	Console_write_line(str);
	Console_set_color(ConsoleColor_gray);
}

static void Console_write_c(const char* str, ConsoleColor color) {
	Console_set_color(color);
	Console_write(str);
	Console_set_color(ConsoleColor_gray);
}


static bool Console_has_input() {
	return _kbhit();
}

static Option_Keys Console_read_key() {
	int rawkey = _getch();
	if (rawkey == 224)
	{
		int rawkey2 = _getch();
		switch (rawkey + rawkey2)
		{
		case Keys_up:
			return Option_Keys_new(Some, Keys_up);
		case Keys_left:
			return Option_Keys_new(Some, Keys_left);
		case Keys_right:
			return Option_Keys_new(Some, Keys_right);
		case Keys_down:
			return Option_Keys_new(Some, Keys_down);
		default:
			return Option_Keys_new(None, None);
		}
	}
	else
		return Option_Keys_new(None, None);
}


static void Console_set_cursor_vis(CursorStat stat) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = stat;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

static void Console_set_pos(int x, int y) {
	COORD pos = { 
		.X = (short)x,
		.Y = (short)y
	};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

static void Console_set_color(ConsoleColor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static void Console_set_size(int x, int y) {
	char str[44];
	sprintf_s(str, sizeof(str), "mode con cols=%d lines=%d", x, y);

	system(str);
}

static void Console_set_title(const char* title) {
	size_t length = strlen(title);
	length += 6 + 1;
	char* str = malloc(length);
	assert(str != NULL);
	sprintf_s(str, length, "title %s", title);

	system(str);
}

static void Console_clear() {
	system("cls");
}