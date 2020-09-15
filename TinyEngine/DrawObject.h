#pragma once

#include "Vector2.h"

struct DrawObject;
typedef struct DrawObject DrawObject;

//struct DrawObject
struct DrawObject {

	//InstanceID Encapsulation
	//private_4byte p4;

	//Name Encapsulation
	//private_p1 pp1_2;

	//sprite data (allocated in stack)
	char32_t** sprite;

	//sprite height
	int height;

	//sprite width
	int width;

	Vector2 (*get_position)(const DrawObject* self);
	void (*set_position)(DrawObject* self, Vector2 vector2);
	int (*get_instanceid)(const DrawObject* self);
	char* (*get_name)(const DrawObject* self);
};