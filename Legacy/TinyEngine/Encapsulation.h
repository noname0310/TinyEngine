#pragma once

#include <stddef.h>
#define PUB __declspec(dllexport)

typedef struct {
	__int32 _4b1;
} private_4byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
} private_8byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
} private_12byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
	__int32 _4b4;
} private_16byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
	__int32 _4b4;
	__int32 _4b5;
} private_20byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
	__int32 _4b4;
	__int32 _4b5;
	__int32 _4b6;
} private_24byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
	__int32 _4b4;
	__int32 _4b5;
	__int32 _4b6;
	__int32 _4b7;
} private_28byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
	__int32 _4b4;
	__int32 _4b5;
	__int32 _4b6;
	__int32 _4b7;
	__int32 _4b8;
} private_32byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
	__int32 _4b4;
	__int32 _4b5;
	__int32 _4b6;
	__int32 _4b7;
	__int32 _4b8;
	__int32 _4b9;
} private_36byte;

typedef struct {
	__int32 _4b1;
	__int32 _4b2;
	__int32 _4b3;
	__int32 _4b4;
	__int32 _4b5;
	__int32 _4b6;
	__int32 _4b7;
	__int32 _4b8;
	__int32 _4b9;
	__int32 _4b10;
} private_40byte;

typedef struct {
	size_t p1;
} private_p1;

typedef struct {
	size_t p1;
	size_t p2;
} private_p2;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
} private_p3;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
	size_t p4;
} private_p4;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
	size_t p4;
	size_t p5;
} private_p5;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
	size_t p4;
	size_t p5;
	size_t p6;
} private_p6;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
	size_t p4;
	size_t p5;
	size_t p6;
	size_t p7;
} private_p7;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
	size_t p4;
	size_t p5;
	size_t p6;
	size_t p7;
	size_t p8;
} private_p8;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
	size_t p4;
	size_t p5;
	size_t p6;
	size_t p7;
	size_t p8;
	size_t p9;
} private_p9;

typedef struct {
	size_t p1;
	size_t p2;
	size_t p3;
	size_t p4;
	size_t p5;
	size_t p6;
	size_t p7;
	size_t p8;
	size_t p9;
	size_t p10;
} private_p10;