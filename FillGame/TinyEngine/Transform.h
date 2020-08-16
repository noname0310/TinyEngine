#pragma once

#include "TinyEngine.h"
#include "Encapsulation.h"

struct _impl_Transform;
typedef struct _impl_Transform _impl_Transform;

struct Transform;
typedef struct Transform Transform;

struct _impl_Transform {
};

struct Transform {
	//position

	//localpositon

	//childcount

	//parent

	//getchild

	//is child of
	
	//set parent
};

TINYENGINE_API Transform Transform_new(int x, int y);