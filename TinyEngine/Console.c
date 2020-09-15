#include "pch.h"
#include "Console.h"

#define MAX_INPUT_LEN 255

def_Option(Keys, Keys)

static void write_line(const char* str, ...);
static void write(const char* str, ...);
static void write_line_c(const char* str, ConsoleColor color, ...);
static void write_c(const char* str, ConsoleColor color, ...);

static bool has_input(void);
static Option_Keys read_key(void);
static const char* read_line();

static void set_cursor_vis(CursorStat stat);
static void set_pos(short x, short y);
static void set_color(ConsoleColor color);
static void set_size(int x, int y);
static void set_title(const wchar_t* title);
static void clear(void);
static void pause(void);

const struct _Console Console = {
	.write_line = write_line,
	.write = write,
	.write_line_c = write_line_c,
	.write_c = write_c,

	.has_input = has_input,
	.read_key = read_key,
	.read_line = read_line,

	.set_cursor_vis = set_cursor_vis,
	.set_pos = set_pos,
	.set_color = set_color,
	.set_size = set_size,
	.set_title = set_title,
	.clear = clear,
	.pause = pause
};

static void write_line(const char* str, ...) {
	assert(str != NULL);
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	printf_s("\n");
}

static void write(const char* str, ...) {
	assert(str != NULL);
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
}

static void write_line_c(const char* str, ConsoleColor color, ...) {
	assert(str != NULL);
	set_color(color);
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	printf_s("\n");
	set_color(ConsoleColor_gray);
}

static void write_c(const char* str, ConsoleColor color, ...) {
	assert(str != NULL);
	set_color(color);
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
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

static const char* read_line() {
	wchar_t wstr[MAX_INPUT_LEN];
	char mb_str[MAX_INPUT_LEN * 3 + 1];

	unsigned long read;
	HANDLE conin = GetStdHandle(STD_INPUT_HANDLE);
	bool a = FlushConsoleInputBuffer(conin);
	ReadConsoleW(conin, wstr, MAX_INPUT_LEN, &read, NULL);
	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL);
	mb_str[size] = 0;
	char* result = malloc(sizeof(mb_str));
	memcpy_s(result, sizeof(mb_str), mb_str, sizeof(mb_str));
	return result;
}

static void set_cursor_vis(CursorStat stat) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = stat;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

static void set_pos(short x, short y) {
	COORD pos = {
		.X = x,
		.Y = y
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

static void set_title(const wchar_t* title) {
	SetConsoleTitle(title);
}

static void clear() {
	system("cls");
}

static void pause() {
	system("pause");
}