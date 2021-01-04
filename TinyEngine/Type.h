#pragma once
#include "Interface.h"

typedef int Type;

#define declexp_get_type_method(type) \
API Type get_type_##type();

#define decl_get_type_method(type) \
Type get_type_##type();

#define def_get_type_method(type) \
Type get_type_##type() { \
	static Type type = -1; \
 \
	if (type == -1) { \
		type = type_indicator; \
		type_indicator += 1; \
	} \
 \
	return type; \
}