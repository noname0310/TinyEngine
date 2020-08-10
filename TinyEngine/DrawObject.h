#pragma once

#include "Encapsulation.h"
#include "Vector2.h"

struct DrawObject;
typedef struct DrawObject DrawObject;

//struct DrawObject
struct DrawObject {

	//InstanceID Encapsulation
	private_4byte p4;

	//Name Encapsulation
	private_p1 pp1_2;

	//sprite data (allocated in stack)
	char** sprite;

	//sprite height
	int height;

	//sprite width
	int width;

	//Vector2 get_position(DrawObject* self)
	Vector2 (*get_position)(DrawObject*);

	//void set_position(DrawObject* self, Vector2 vector2)
	void (*set_position)(DrawObject*, Vector2);

	//int get_instanceid(DrawObject* self)
	int (*get_instanceid)(DrawObject*);

	//char* get_name(DrawObject* self)
	char* (*get_name)(DrawObject*);
};