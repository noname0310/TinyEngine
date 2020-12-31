#include "pch.h"
#include "Object.h"

def_get_type_method(Object)

static const wchar_t* get_name(const Object* self);
static const int get_instance_id(const Object* self);
static void instantlate(const Object* self);
static void destroy(const Object* self);

const impl_Object* get_impl_Object_table() {
	static impl_Object impl_Object_table = {
		.get_type = get_type_Object,
		.get_name = get_name,
		.get_instance_id = get_instance_id,
		.instantlate = instantlate,
		.destroy = destroy
	};
	return &impl_Object_table;
}

Object Object_new(void* iter, const wchar_t name[], int instance_id) {
	assert(name != NULL);
	size_t length = wcslen(name) * sizeof(wchar_t);
	box_byref(wchar_t*, name, length + sizeof(wchar_t))

	private_Object p_instance = {
		.name = name_boxed,
		.instance_id = instance_id//need to edit
	};

	Object instance = {
		.f = get_impl_Object_table(),
		.iter = iter,
		.private_Object = p_instance
	};

	return instance;
}

static const wchar_t* get_name(const Object* self) {
	assert(self != NULL);
	return self->private_Object.name;
}

static const int get_instance_id(const Object* self) {
	assert(self != NULL);
	return self->private_Object.instance_id;
}

static void instantlate(const Object* self) {
	assert(self != NULL);

}

static void destroy(const Object* self) {
	assert(self != NULL);
	free(self->private_Object.name);
}
