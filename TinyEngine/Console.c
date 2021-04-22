#include "pch.h"
#include "Console.h"

#define MAX_INPUT_LEN 257

def_Option(Keys, Keys)

static void write_line(const wchar_t str[], ...);
static void write(const wchar_t str[], ...);
static void write_single(wchar_t ch);
static void write_line_c(const wchar_t str[], ConsoleColor color, ...);
static void write_c(const wchar_t str[], ConsoleColor color, ...);
static void write_single_c(wchar_t ch, ConsoleColor color);

static bool has_input(void);
static Option_Keys read_key(void);
static const wchar_t* read_line();

static void set_cursor_vis(CursorStat stat);
static void set_pos(short x, short y);
static void set_color(ConsoleColor color);
static void set_size(int x, int y);
static void set_title(const wchar_t title[]);
static void set_codepage(CodePage codepage);
static void set_locale2utf8(void);
static void default_init(void);
static void font_normalize(int size);
static void clear(void);
static void pause(void);

const _Console Console = {
	.write_line = write_line,
	.write = write,
	.write_single = write_single,
	.write_line_c = write_line_c,
	.write_c = write_c,
	.write_single_c = write_single_c,

	.has_input = has_input,
	.read_key = read_key,
	.read_line = read_line,

	.set_cursor_vis = set_cursor_vis,
	.set_pos = set_pos,
	.set_color = set_color,
	.set_size = set_size,
	.set_title = set_title,
	.set_codepage = set_codepage,
	.set_locale2utf8 = set_locale2utf8,
	.default_init = default_init,
	.font_normalize = font_normalize,
	.clear = clear,
	.pause = pause
};

static void write_line(const wchar_t str[], ...) {
	assert(str != NULL);
	va_list args;
	va_start(args, str); 
	vwprintf(str, args);
	va_end(args);
	wprintf_s(L"\n");
}

static void write(const wchar_t str[], ...) {
	assert(str != NULL);
	va_list args;
	va_start(args, str);
	vwprintf(str, args);
	va_end(args);
}

static void write_single(wchar_t ch) {
	putwchar(ch);
}

static void write_line_c(const wchar_t str[], ConsoleColor color, ...) {
	assert(str != NULL);
	set_color(color);
	va_list args;
	va_start(args, str);
	vwprintf(str, args);
	va_end(args);
	wprintf_s(L"\n");
	set_color(ConsoleColor_gray);
}

static void write_c(const wchar_t str[], ConsoleColor color, ...) {
	assert(str != NULL);
	set_color(color);
	va_list args;
	va_start(args, str);
	vwprintf(str, args);
	va_end(args);
	set_color(ConsoleColor_gray);
}

static void write_single_c(wchar_t ch, ConsoleColor color) {
	set_color(color);
	putwchar(ch);
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
			return Option_Keys_some(Keys_up);
		case Keys_left:
			return Option_Keys_some(Keys_left);
		case Keys_right:
			return Option_Keys_some(Keys_right);
		case Keys_down:
			return Option_Keys_some(Keys_down);
		default:
			return Option_Keys_some(None);
		}
	}
	else
		return Option_Keys_none();
}

static const wchar_t* read_line() {
	wchar_t wstr[MAX_INPUT_LEN] = { 0 };

	HANDLE conin = GetStdHandle(STD_INPUT_HANDLE);
	assert(conin != INVALID_HANDLE_VALUE);
	bool flush_result = FlushConsoleInputBuffer(conin);
	assert(flush_result != false);
	unsigned long read = 0;
	bool read_result = ReadConsoleW(conin, wstr, MAX_INPUT_LEN, &read, NULL);
	assert(read_result != false);
	int readbyte = read * sizeof(wchar_t);
	
	if (wstr[read - 2] == L'\r') {
		wstr[read - 2] = L'\0';
		wchar_t* result = malloc((size_t)(readbyte - 1));
		assert(result != NULL || !"malloc failed");
		memcpy_s(result, (size_t)(readbyte - 1), wstr, (size_t)(readbyte - 1));
		return result;
	}
	else if (wstr[read - 1] == '\n') {
		wstr[read - 1] = L'\0';
		wchar_t* result = malloc(readbyte);
		assert(result != NULL || !"malloc failed");
		memcpy_s(result, readbyte, wstr, readbyte);
		return result;
	}
	else if (wstr[read - 1] != '\0') {
		wchar_t* result = malloc(readbyte);
		assert(result != NULL || !"malloc failed");
		memcpy_s(result, readbyte, wstr, readbyte);
		return result;
	}
	else {
		wchar_t* result = malloc(readbyte);
		assert(result != NULL || !"malloc failed");
		memcpy_s(result, readbyte, wstr, readbyte);
		return result;
	}
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

static void set_title(const wchar_t title[]) {
	SetConsoleTitle(title);
}

static void set_codepage(CodePage codepage) {
	SetConsoleOutputCP(codepage);
	SetConsoleCP(codepage);
}

static void set_locale2utf8() {
	setlocale(LC_ALL, ".UTF8");
}

static void default_init() {
	set_codepage(CodePage_Utf8);
	set_locale2utf8();
}

static void font_normalize(int size) {
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FW_NORMAL;
	const wchar_t myFont[] = L"GulimChe";
	fontInfo.dwFontSize.X = size;
	fontInfo.dwFontSize.Y = size;
	memcpy(fontInfo.FaceName, myFont, sizeof(myFont));
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &fontInfo);
}

static void clear() {
	system("cls");
}

static void pause() {
	system("pause");
}
