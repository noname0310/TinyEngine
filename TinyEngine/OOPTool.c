#include "pch.h"
#include "OOPTool.h"

static void set_const(const void* target, const void* value);
static void set_const_value(const void* target, const void* value, size_t size);

const _OOPTool OOPTool = {
	.set_const = set_const,
	.set_const_value = set_const_value
};

static void set_const(const void* target, const void* value) {
	memcpy_s((void* const)target, sizeof(void*), &value, sizeof(void*));
}

static void set_const_value(const void* target, const void* value, size_t size) {
	memcpy_s((void* const)target, size, value, size);
}
