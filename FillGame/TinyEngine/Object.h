#pragma once

#include "TinyEngine.h"
struct _impl_Object;
typedef struct _impl_Object impl_Object;

struct private_Object;
typedef struct private_Object private_Object;

struct Object;
typedef struct Object Object;

struct _impl_Object {
	//int get_instance_id(Object* self)
	int (*get_instance_id)(Object*);

	//int get_instance_id(Object* self)
	int (*get_instance_id)(Object*);

	//int destroy(Object* self)
	int (*destroy)(Object*);
};

struct private_Object {
	char* name;
	int instanceID;
};

struct Object {
	private_Object p;
	impl_Object* f;
};

Object Object_new(const char* name);
Object Object_instantlate(const char* name);