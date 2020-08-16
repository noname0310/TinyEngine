#include "pch.h"
#include "Console.h"
def_Option(Keys);

static void write_line(const char* str);
static void write(const char* str);
static void write_line_c(const char* str, ConsoleColor color);
static void write_c(const char* str, ConsoleColor color);

static bool has_input(void);
static Option_Keys read_key(void);

static void set_cursor_vis(CursorStat stat);
static void set_pos(int x, int y);
static void set_color(ConsoleColor color);
static void set_size(int x, int y);
static void set_title(const char* title);
static void clear(void);

PUB struct _Console Console = {
	.write_line = write_line,
	.write = write,
	.write_line_c = write_line_c,
	.write_c = write_c,

	.has_input = has_input,
	.read_key = read_key,

	.set_cursor_vis = set_cursor_vis,
	.set_pos = set_pos,
	.set_color = set_color,
	.set_size = set_size,
	.set_title = set_title,
	.clear = clear
};

static void write_line(const char* str) {
	printf_s("%s\n", str);
}

static void write(const char* str) {
	printf_s(str);
}

static void write_line_c(const char* str, ConsoleColor color) {
	set_color(color);
	write_line(str);
	set_color(ConsoleColor_gray);
}

static void write_c(const char* str, ConsoleColor color) {
	set_color(color);
	write(str);
	set_color(ConsoleColor_gray);
}


static bool has_input() {
	return _kbhit();
}

static Option_Keys read_key() {
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


static void set_cursor_vis(CursorStat stat) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = stat;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

static void set_pos(int x, int y) {
	COORD pos = { 
		.X = (short)x,
		.Y = (short)y
	};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

static void set_color(ConsoleColor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static void set_size(int x, int y) {
	char str[44];
	sprintf_s(str, sizeof(str), "mode con cols=%d lines=%d", x, y);

	system(str);
}

static void set_title(const char* title) {
	size_t length = strlen(title);
	length += 6 + 1;
	char* str = malloc(length);
	assert(str != NULL);
	sprintf_s(str, length, "title %s", title);

	system(str);
}

static void clear() {
	system("cls");
}