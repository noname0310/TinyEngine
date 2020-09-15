#include "pch.h"
#include "Object.h"

def_get_type_method(Object)

static const char* get_name(const Object* self);
static const int get_instance_id(const Object* self);
static void instantlate(const Object* self);
static void destroy(const Object* self);

const impl_Object* get_impl_Object_table() {
	static impl_Object impl_Object_table = {
	.get_name = get_name,
	.get_instance_id = get_instance_id,
	.instantlate = instantlate,
	.destroy = destroy
	};
	return &impl_Object_table;
}

Object Object_new(void* iter, const char* name, int instance_id) {
	assert(name != NULL);
	size_t length = strlen(name);
	box_byref(char*, name, length + 1)

	private_Object p_instance = {
		.name = name_boxed,
		.instance_id = instance_id//need to edit
	};

	Object instance = {
		.f = get_impl_Object_table(),
		.get_type = get_type_Object,
		.iter = iter,
		.p = p_instance
	};

	return instance;
}

static const char* get_name(const Object* self) {
	assert(self != NULL);
	return self->p.name;
}

static const int get_instance_id(const Object* self) {
	assert(self != NULL);
	return self->p.instance_id;
}

static void instantlate(const Object* self) {
	assert(self != NULL);

}

static void destroy(const Object* self) {
	assert(self != NULL);
	free(self->p.name);
}