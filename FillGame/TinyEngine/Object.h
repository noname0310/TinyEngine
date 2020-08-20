#pragma once

#include <string.h>
#include <vcruntime.h>
#include <assert.h>
#include "TinyEngine.h"
#include "Box.h"
#include "Interface.h"

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
	//const char* get_name(const Object* self)
	const char* (*get_name)(const Object*);

	//int get_instance_id(const Object* self)
	const int (*get_instance_id)(const Object*);

	//void instantlate(const Object* self)
	void (*instantlate)(const Object*);

	//void destroy(const Object* self)
	void (*destroy)(const Object*);
};

struct Object {
	//int get_type() - overloaded
	int (*get_type)();

	private_Object p;
	void* iter;
	impl_Object* f;
};

TINYENGINE_API Object Object_new(const void* iter, const char* name, int instance_id);