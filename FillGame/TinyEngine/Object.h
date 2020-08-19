#pragma once

#include <string.h>
#include <vcruntime.h>
#include "TinyEngine.h"
#include "Box.h"
#include "Interface.h"

struct _impl_Object;
typedef struct _impl_Object impl_Object;

struct private_Object;
typedef struct private_Object private_Object;

struct Object;
typedef struct Object Object;

struct _impl_Object {
	//const char* get_name(Object* self)
	const char* (*get_name)(Object*);

	//int get_instance_id(Object* self)
	int (*get_instance_id)(Object*);

	//void instantlate(Object* self)
	void (*instantlate)(Object*);

	//void destroy(Object* self)
	void (*destroy)(Object*);
};

struct private_Object {
	char* name;
	int instance_id;
};

struct Object {
	//int get_type() - overloaded
	int (*get_type)();

	private_Object p;
	impl_Object* f;
};

TINYENGINE_API Object Object_new(const char* name, int instance_id);