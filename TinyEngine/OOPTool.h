#pragma once

#include <corecrt_memcpy_s.h>
#include "TinyEngine.h"

struct _OOPTool;
typedef struct _OOPTool _OOPTool;

struct _OOPTool {
	void (*const set_const)(const void* target, const void* value);
	void (*const set_const_value)(const void* target, const void* value, size_t size);
};

extern TINYENGINE_API const _OOPTool OOPTool;
