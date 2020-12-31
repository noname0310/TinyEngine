#pragma once

#include <string.h>
#include <assert.h>
#include "TinyEngine.h"
#include "Box.h"
#include "Type.h"
#include "Object.h"
#include "OOPTool.h"

struct private_GameObject;
typedef struct private_GameObject private_GameObject;

struct impl_GameObject;
typedef struct impl_GameObject impl_GameObject;

struct GameObject;
typedef struct GameObject GameObject;

//struct private_GameObject {
//
//};

struct impl_GameObject {
	impl_Object_Members

#define impl_GameObject_Members \
	void* (*const get_component)(const GameObject* self, Type type);

	impl_GameObject_Members
};

struct GameObject {
	const impl_GameObject* const f;
	Object_Members

#define GameObject_Members \
	//private_GameObject private_GameObject;

	GameObject_Members
};

TINYENGINE_API GameObject GameObject_new(void* iter, const wchar_t name[], int instance_id);
TINYENGINE_API const impl_GameObject* get_impl_GameObject_table();
declexp_get_type_method(GameObject);
