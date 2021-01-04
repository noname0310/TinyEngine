#pragma once

#include <stdlib.h>
#include <assert.h>
#include <corecrt_memcpy_s.h>
#include "TinyEngine.h"

#define box(T, V) \
T* V##_boxed = (T*)malloc(sizeof(T)); \
assert(V##_boxed != NULL || !"malloc failed"); \
memcpy(V##_boxed, &V, sizeof(T));

#define box_byref(T, V, S) \
T V##_boxed = (T)malloc(S); \
assert(V##_boxed != NULL || !"malloc failed"); \
memcpy(V##_boxed, V, S);

struct _OOPTool;
typedef struct _OOPTool _OOPTool;

struct _OOPTool {
	void (*const set_const)(const void* target, const void* value);
	void (*const set_const_value)(const void* target, const void* value, size_t size);
};

extern API const _OOPTool OOPTool;
