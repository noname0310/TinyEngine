#pragma once

#define decl_Option(T) \
\
typedef struct { \
    Option option; \
    T value; \
} Option_##T; \
\
Option_##T Option_##T##_new(Option opt, T val);

#define def_Option(T) \
\
Option_##T Option_##T##_new(Option opt, T val) \
{ \
    Option_##T temp = { \
        .option = opt, \
        .value = val \
    }; \
    return temp;\
}

enum _Option;
typedef enum _Option Option;

enum _Option {
    Some,
    None
};