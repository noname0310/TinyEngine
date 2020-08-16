#pragma once

#include "TinyEngine.h"
#include "Encapsulation.h"

struct _impl_Component;
typedef struct _impl_Component _impl_Component;

struct Component;
typedef struct Component Component;

struct _impl_Component {
};

struct Component {
	//position

	//localpositon

	//childcount

	//parent

	//getchild

	//is child of

	//set parent
};

TINYENGINE_API Transform Transform_new(int x, int y);