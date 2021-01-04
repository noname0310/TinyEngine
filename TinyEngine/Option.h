#pragma once

#include "TinyEngine.h"

#define declexp_Option(T, declname) \
\
typedef struct { \
    Option option; \
    T value; \
} Option_##declname; \
\
/*API Option_##declname Option_##declname##_new(Option opt, T val);*/ \
API Option_##declname Option_##declname##_some(T val); \
API Option_##declname Option_##declname##_none();

#define decl_Option(T, declname) \
\
typedef struct { \
    Option option; \
    T value; \
} Option_##declname; \
\
/*Option_##declname Option_##declname##_new(Option opt, T val);*/ \
Option_##declname Option_##declname##_some(T val); \
Option_##declname Option_##declname##_none();

#define def_Option(T, declname) \
\
/*Option_##declname Option_##declname##_new(Option opt, T val)*/ \
/*{*/ \
/*    Option_##declname temp = {*/ \
/*        .option = opt,*/ \
/*        .value = val*/ \
/*    };*/ \
/*    return temp;*/ \
/*}*/ \
 \
Option_##declname Option_##declname##_some(T val) \
{ \
    Option_##declname instance = { \
        .option = Some, \
        .value = val \
    }; \
    return instance; \
} \
 \
Option_##declname Option_##declname##_none() \
{ \
    Option_##declname instance = { \
        .option = None, \
        .value = 0 \
    }; \
    return instance; \
}

enum _Option;
typedef enum _Option Option;

enum _Option {
    None = 0,
    Some = 1
};

declexp_Option(char, char)
declexp_Option(wchar_t, wchar_t)
declexp_Option(short, short)
declexp_Option(int, int)
declexp_Option(long long int, int64)
declexp_Option(float, float)
declexp_Option(double, double)
declexp_Option(const wchar_t*, c_str)
