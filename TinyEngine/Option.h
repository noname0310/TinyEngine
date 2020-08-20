#pragma once

#include "TinyEngine.h"

#define declexp_Option(T, declname) \
\
typedef struct { \
    Option option; \
    T value; \
} Option_##declname; \
\
TINYENGINE_API Option_##declname Option_##declname##_new(Option opt, T val);

#define decl_Option(T, declname) \
\
typedef struct { \
    Option option; \
    T value; \
} Option_##declname; \
\
Option_##declname Option_##declname##_new(Option opt, T val);

#define def_Option(T, declname) \
\
Option_##declname Option_##declname##_new(Option opt, T val) \
{ \
    Option_##declname temp = { \
        .option = opt, \
        .value = val \
    }; \
    return temp; \
}

enum _Option;
typedef enum _Option Option;

enum _Option {
    None = 0,
    Some = 1
};