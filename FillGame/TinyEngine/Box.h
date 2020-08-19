#pragma once

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define box(T, V) \
T* V##_boxed = (T*)malloc(sizeof(T)); \
assert(V##_boxed != NULL || !"malloc failed"); \
memcpy(V##_boxed, &V, sizeof(T));

#define box_byref(T, V, S) \
T V##_boxed = (T)malloc(S); \
assert(V##_boxed != NULL || !"malloc failed"); \
memcpy(V##_boxed, V, S);