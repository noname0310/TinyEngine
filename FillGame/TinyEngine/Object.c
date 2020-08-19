#include "pch.h"
#include "Object.h"

static int get_type();

static const char* get_name(Object* self);
static int get_instance_id(Object* self);
static void instantlate(Object* self);
static void destroy(Object* self);

impl_Object impl_Object_table = {
	.get_name = get_name,
	.get_instance_id = get_instance_id,
	.instantlate = instantlate,
	.destroy = destroy
};

Object Object_new(const char* name, int instance_id) {
	size_t length = strlen(name);
	box_byref(char*, name, length + 1)

	private_Object p_instance = {
		.name = name_boxed,
		.instance_id = instance_id//need to edit
	};

	Object instance = {
		.get_type = get_type,
		.p = p_instance,
		.f = &impl_Object_table
	};

	return instance;
}

static int get_type() {
	static int type = -1;

	if (type == -1) {
		type = type_indicator;
		type_indicator += 1;
	}

	return type;
}

static const char* get_name(Object* self) {
	return self->p.name;
}

static int get_instance_id(Object* self) {
	return self->p.instance_id;
}

static void instantlate(Object* self) {

}

static void destroy(Object* self) {
	free(self->p.name);
}