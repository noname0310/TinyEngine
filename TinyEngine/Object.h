#pragma once

#include <string.h>
#include <assert.h>
#include "TinyEngine.h"
#include "Box.h"
#include "Type.h"

struct private_Object;
typedef struct private_Object private_Object;

struct impl_Object;
typedef struct impl_Object impl_Object;

struct Object;
typedef struct Object Object;

struct private_Object {
	char* name;
	int instance_id;
};

struct impl_Object {
#define impl_Object_Members \
	const char* (*get_name)(const Object* self); \
	const int (*get_instance_id)(const Object* self); \
	void (*instantlate)(const Object* self); \
	void (*destroy)(const Object* self);

	impl_Object_Members
};

struct Object {
	const impl_Object* const f;

#define Object_Members \
	/*Type get_type() - overloaded*/ \
	Type (*get_type)(); \
	void* iter; \
	private_Object p;

	Object_Members
};

TINYENGINE_API Object Object_new(void* iter, const char name[], int instance_id);
TINYENGINE_API const impl_Object* get_impl_Object_table();
declexp_get_type_method(Object);