#pragma once

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include <assert.h>
#include <stdarg.h>
#include <locale.h>
#include "TinyEngine.h"
#include "Option.h"

struct _Console; 
typedef struct _Console _Console;

enum ConsoleColor;
typedef enum ConsoleColor ConsoleColor;

enum CursorStat;
typedef enum CursorStat CursorStat;

enum Keys;
typedef enum Keys Keys;

declexp_Option(Keys, Keys)

enum CodePage;
typedef enum CodePage CodePage;

//Struct _Console
struct _Console {
	void (*const write_line)(const wchar_t str[], ...);
	void (*const write)(const wchar_t str[], ...);
	void (*const write_line_c)(const wchar_t str[], ConsoleColor color, ...);
	void (*const write_c)(const wchar_t str[], ConsoleColor color, ...);
	bool (*const has_input)();
	Option_Keys (*const read_key)();
	const wchar_t* (*const read_line)();
	void (*const set_cursor_vis)(CursorStat stat);
	void (*const set_pos)(short x, short y);
	void (*const set_color)(ConsoleColor color);
	void (*const set_size)(int x, int y);
	void (*const set_title)(const wchar_t title[]);
	void (*const set_codepage)(CodePage codepage);
	void (*const set_locale2utf8)();
	void (*const default_init)();
	void (*const font_normalize)();
	void (*const clear)();
	void (*const pause)();
};

extern API const _Console Console;

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

enum CodePage {
	CodePage_Default = 0,
	CodePage_IBM037 = 37,
	CodePage_IBM437 = 437,
	CodePage_IBM500 = 500,
	CodePage_ASMO708 = 708,
	CodePage_DOS720 = 720,
	CodePage_Ibm737 = 737,
	CodePage_Ibm775 = 775,
	CodePage_Ibm850 = 850,
	CodePage_Ibm852 = 852,
	CodePage_IBM855 = 855,
	CodePage_Ibm857 = 857,
	CodePage_IBM00858 = 858,
	CodePage_IBM860 = 860,
	CodePage_Ibm861 = 861,
	CodePage_DOS862 = 862,
	CodePage_IBM863 = 863,
	CodePage_IBM864 = 864,
	CodePage_IBM865 = 865,
	CodePage_Cp866 = 866,
	CodePage_Ibm869 = 869,
	CodePage_IBM870 = 870,
	CodePage_Windows874 = 874,
	CodePage_Cp875 = 875,
	CodePage_Shiftjis = 932,
	CodePage_Gb2312 = 936,
	CodePage_Ksc56011987 = 949,
	CodePage_Big5 = 950,
	CodePage_IBM1026 = 1026,
	CodePage_IBM01047 = 1047,
	CodePage_IBM01140 = 1140,
	CodePage_IBM01141 = 1141,
	CodePage_IBM01142 = 1142,
	CodePage_IBM01143 = 1143,
	CodePage_IBM01144 = 1144,
	CodePage_IBM01145 = 1145,
	CodePage_IBM01146 = 1146,
	CodePage_IBM01147 = 1147,
	CodePage_IBM01148 = 1148,
	CodePage_IBM01149 = 1149,
	CodePage_Utf16 = 1200,
	CodePage_UnicodeFFFE = 1201,
	CodePage_Windows1250 = 1250,
	CodePage_Windows1251 = 1251,
	CodePage_Windows1252 = 1252,
	CodePage_Windows1253 = 1253,
	CodePage_Windows1254 = 1254,
	CodePage_Windows1255 = 1255,
	CodePage_Windows1256 = 1256,
	CodePage_Windows1257 = 1257,
	CodePage_Windows1258 = 1258,
	CodePage_Johab = 1361,
	CodePage_Macintosh = 10000,
	CodePage_Xmacjapanese = 10001,
	CodePage_Xmacchinesetrad = 10002,
	CodePage_Xmackorean = 10003,
	CodePage_Xmacarabic = 10004,
	CodePage_Xmachebrew = 10005,
	CodePage_Xmacgreek = 10006,
	CodePage_Xmaccyrillic = 10007,
	CodePage_Xmacchinesesimp = 10008,
	CodePage_Xmacromanian = 10010,
	CodePage_Xmacukrainian = 10017,
	CodePage_Xmacthai = 10021,
	CodePage_Xmacce = 10029,
	CodePage_Xmacicelandic = 10079,
	CodePage_Xmacturkish = 10081,
	CodePage_Xmaccroatian = 10082,
	CodePage_Utf32 = 12000,
	CodePage_Utf32BE = 12001,
	CodePage_XChineseCNS = 20000,
	CodePage_Xcp20001 = 20001,
	CodePage_XChineseEten = 20002,
	CodePage_Xcp20003 = 20003,
	CodePage_Xcp20004 = 20004,
	CodePage_Xcp20005 = 20005,
	CodePage_XIA5 = 20105,
	CodePage_XIA5German = 20106,
	CodePage_XIA5Swedish = 20107,
	CodePage_XIA5Norwegian = 20108,
	CodePage_UsAscii = 20127,
	CodePage_Xcp20261 = 20261,
	CodePage_Xcp20269 = 20269,
	CodePage_IBM273 = 20273,
	CodePage_IBM277 = 20277,
	CodePage_IBM278 = 20278,
	CodePage_IBM280 = 20280,
	CodePage_IBM284 = 20284,
	CodePage_IBM285 = 20285,
	CodePage_IBM290 = 20290,
	CodePage_IBM297 = 20297,
	CodePage_IBM420 = 20420,
	CodePage_IBM423 = 20423,
	CodePage_IBM424 = 20424,
	CodePage_XEBCDICKoreanExtended = 20833,
	CodePage_IBMThai = 20838,
	CodePage_Koi8r = 20866,
	CodePage_IBM871 = 20871,
	CodePage_IBM880 = 20880,
	CodePage_IBM905 = 20905,
	CodePage_IBM00924 = 20924,
	CodePage_EUCJP_1990 = 20932,
	CodePage_Xcp20936 = 20936,
	CodePage_Xcp20949 = 20949,
	CodePage_Cp1025 = 21025,
	CodePage_Koi8u = 21866,
	CodePage_Iso88591 = 28591,
	CodePage_Iso88592 = 28592,
	CodePage_Iso88593 = 28593,
	CodePage_Iso88594 = 28594,
	CodePage_Iso88595 = 28595,
	CodePage_Iso88596 = 28596,
	CodePage_Iso88597 = 28597,
	CodePage_Iso88598 = 28598,
	CodePage_Iso88599 = 28599,
	CodePage_Iso885913 = 28603,
	CodePage_Iso885915 = 28605,
	CodePage_XEuropa = 29001,
	CodePage_Iso88598i = 38598,
	CodePage_Iso2022jp = 50220,
	CodePage_CsISO2022JP = 50221,
	CodePage_Iso2022jpOneByte = 50222,
	CodePage_Iso2022kr = 50225,
	CodePage_Xcp50227 = 50227,
	CodePage_Eucjp = 51932,
	CodePage_EUCCN = 51936,
	CodePage_Euckr = 51949,
	CodePage_Hzgb2312 = 52936,
	CodePage_GB18030 = 54936,
	CodePage_Xisciide = 57002,
	CodePage_Xisciibe = 57003,
	CodePage_Xisciita = 57004,
	CodePage_Xisciite = 57005,
	CodePage_Xisciias = 57006,
	CodePage_Xisciior = 57007,
	CodePage_Xisciika = 57008,
	CodePage_Xisciima = 57009,
	CodePage_Xisciigu = 57010,
	CodePage_Xisciipa = 57011,
	CodePage_Utf7 = 65000,
	CodePage_Utf8 = 65001
};
