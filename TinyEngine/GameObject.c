#include "pch.h"
#include "GameObject.h"

def_get_type_method(GameObject)

static void* get_component(const GameObject* self, Type type);

const impl_GameObject* get_impl_GameObject_table() {
	static impl_GameObject impl_GameObject_table = {
		.get_component = get_component
	};
	
	if (*(void**)&impl_GameObject_table == NULL) {
		memcpy_s(
			&impl_GameObject_table,
			sizeof(impl_Object),
			get_impl_Object_table(),
			sizeof(impl_Object)
		);
	}

	return &impl_GameObject_table;
}

GameObject GameObject_new(void* iter, const char* name, int instance_id) {
	Object parent_instance = Object_new(iter, name, instance_id);

	//private_GameObject p_instance = { 
	//	
	//};

	GameObject instance = {
		.f = get_impl_GameObject_table(),
		//.p1 = p_instance,
	};

	memcpy_s(
		(size_t*)(&instance) + 1,
		sizeof(Object) - sizeof(size_t),
		(size_t*)(&parent_instance) + 1,
		sizeof(Object) - sizeof(size_t)
	);

	instance.get_type = get_type_GameObject;

	return instance;
}

static void* get_component(const GameObject* self, Type type) {
	assert(self != NULL);
	return NULL;
}