#pragma once

#include <string.h>
#include <assert.h>
#include <wchar.h>
#include "TinyEngine.h"
#include "Type.h"
#include "OOPTool.h"

struct private_Object;
typedef struct private_Object private_Object;

struct impl_Object;
typedef struct impl_Object impl_Object;

struct Object;
typedef struct Object Object;

struct private_Object {
	wchar_t* name;
	int instance_id;
};

struct impl_Object {
#define impl_Object_Members \
	Type (*const get_type)(); \
	const wchar_t* (*const get_name)(const Object* self); \
	const int (*const get_instance_id)(const Object* self); \
	void (*const instantlate)(const Object* self); \
	void (*const destroy)(const Object* self);

	impl_Object_Members
};

struct Object {
	const impl_Object* const f;

#define Object_Members \
	void* iter; \
	private_Object private_Object;

	Object_Members
};

API Object Object_new(void* iter, const wchar_t name[], int instance_id);
API const impl_Object* get_impl_Object_table();
declexp_get_type_method(Object);
