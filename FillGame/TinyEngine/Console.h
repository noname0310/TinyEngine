#pragma once

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include <assert.h>
#include <stdarg.h>
#include "Option.h"
#include "Encapsulation.h"
#include "TinyEngine.h"

struct _Console;

enum ConsoleColor;
typedef enum ConsoleColor ConsoleColor;

enum CursorStat;
typedef enum CursorStat CursorStat;

enum Keys;
typedef enum Keys Keys;

decl_Option(Keys)

//Struct _Console
struct _Console {
	//void write_line(const char* str)
	void (*write_line)(const char*);

	//void write(const char* str)
	void (*write)(const char*);

	//void write_line(const char* str, ConsoleColor color)
	void (*write_line_c)(const char*, ConsoleColor);

	//void write_c(const char* str, ConsoleColor color)
	void (*write_c)(const char*, ConsoleColor);

	//bool has_input()
	bool (*has_input)();

	//Option_Keys read_key()
	Option_Keys(*read_key)();

	//void set_cursor_vis()
	void (*set_cursor_vis)(CursorStat);

	//void set_pos(int x, int y)
	void (*set_pos)(int, int);

	//void set_color(ConsoleColor color)
	void (*set_color)(ConsoleColor);

	//void set_size(int x, int y)
	void (*set_size)(int, int);

	//void set_title(const char* title)
	void (*set_title)(const char*);

	//void clear()
	void (*clear)();
};

extern TINYENGINE_API struct _Console Console;

//Enum ConsoleColor
enum ConsoleColor {
	//default background color
	ConsoleColor_black = 0,
	ConsoleColor_darkblue = 1,
	ConsoleColor_darkgreen = 2,
	ConsoleColor_darkcyan = 3,
	ConsoleColor_darkred = 4,
	ConsoleColor_darkmagenta = 5,
	ConsoleColor_darkyellow = 6,
	//default text color
	ConsoleColor_gray = 7,
	ConsoleColor_darkgray = 8,
	ConsoleColor_blue = 9,
	ConsoleColor_green = 10,
	ConsoleColor_cyan = 11,
	ConsoleColor_red = 12,
	ConsoleColor_magenta = 13,
	ConsoleColor_yellow = 14,
	ConsoleColor_white = 15
};

//Enum ConsoleCursorStat
enum CursorStat {
	CursorStat_hide = 0,
	CursorStat_show = 1
};

enum Keys {
	Keys_up = 224 + 72,
	Keys_left = 224 + 75,
	Keys_right = 224 + 77,
	Keys_down = 224 + 80,
};