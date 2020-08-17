#pragma once

#include <stdlib.h>
#include <string.h>

#define box(T, V) \
T* V##_boxed = (T*)malloc(sizeof(T)); \
assert(V##_boxed != NULL || !"malloc failed"); \
memcpy(V##_boxed, &V, sizeof(T));