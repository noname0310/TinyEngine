#include "pch.h"
#include "GameObject.h"

def_get_type_method(GameObject)

static void* get_component(const GameObject* self, Type type);

const impl_GameObject* get_impl_GameObject_table() {
	static impl_GameObject impl_GameObject_table = {
		.get_component = get_component
	};
	
	if (*(void**)&impl_GameObject_table == NULL) {
		OOPTool.set_const_value(&impl_GameObject_table, get_impl_Object_table(), sizeof(impl_Object));
		OOPTool.set_const(&impl_GameObject_table.get_type, get_type_GameObject);
	}

	return &impl_GameObject_table;
}

GameObject GameObject_new(void* iter, const wchar_t name[], int instance_id) {
	Object parent_instance = Object_new(iter, name, instance_id);

	//private_GameObject p_instance = { 
	//	
	//};

	GameObject instance = {
		.f = get_impl_GameObject_table(),
		//.p1 = p_instance,
	};

	OOPTool.set_const_value((size_t*)(&instance) + 1, (size_t*)(&parent_instance) + 1, sizeof(Object) - sizeof(size_t));

	return instance;
}

static void* get_component(const GameObject* self, Type type) {
	assert(self != NULL);
	return NULL;
}
