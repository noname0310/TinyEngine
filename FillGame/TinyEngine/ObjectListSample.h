#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "TinyEngine.h"
#include "Object.h"
#include "Box.h"

struct private_List_Object;
typedef struct private_List_Object private_List_Object;

struct impl_List_Object;
typedef struct impl_List_Object impl_List_Object;

struct List_Object;
typedef struct List_Object List_Object;

struct private_Node_Object;
typedef struct private_Node_Object private_Node_Object;

struct impl_Node_Object;
typedef struct impl_Node_Object impl_Node_Object;

struct Node_Object;
typedef struct Node_Object Node_Object;

struct private_List_Object {
    int length;
    Node_Object* first;
    Node_Object* last;
};

struct impl_List_Object {
    /* void clear(const List_Object* self, void (*disposefn)(const Object*)) */
    void (*clear)(List_Object*, void (*)(const Object*));
    /* int get_length(const List_Object* self) */
    int (*get_length)(const List_Object*);
    /* bool is_empty(const List_Object* self) */
    bool (*is_empty)(const List_Object*);

    /* Object get_front(const List_Object* self) */
    Object* (*get_front)(const List_Object*);
    /* void push_front(List_Object* self, const Object* value) */
    void (*push_front)(List_Object*, const Object*);
    /* void pop_front(List_Object* self, void (*disposefn)(const Object*)) */
    void (*pop_front)(List_Object*, void (*)(const Object*));
    /* Object get_back(const List_Object* self) */
    Object* (*get_back)(const List_Object*);
    /* void push_back(List_Object* self, const Object* value) */
    void (*push_back)(List_Object*, const Object*);
    /* void pop_back(List_Object* self, void (*disposefn)(const Object*)) */
    void (*pop_back)(List_Object*, void (*)(const Object*));

    /* Node_Object* insert(List_Object* self, const Node_Object* pos, const Object* value) */
    Node_Object* (*insert)(List_Object*, const Node_Object*, const Object*);
    /* void remove(List_Object* self, const Node_Object* pos, void (*disposefn)(const Object*)) */
    void (*remove)(List_Object*, const Node_Object*, void (*)(const Object*));
    /* bool contains(const List_Object* self, const Object* value) */
    bool (*contains)(const List_Object*, const Object*);
    /* void for_each(const List_Object* self, void (*fn)(const Object*)) lambda*/
    void (*for_each)(const List_Object*, void (*)(const Object*));
};

struct List_Object {
    private_List_Object p;
    impl_List_Object* f;
};

struct private_Node_Object {
    Node_Object* prev;
    Object* value;
    Node_Object* next;
};

struct impl_Node_Object {
    /* Node_Object* get_prev(const Node_Object* self) */
    Node_Object* (*get_prev)(const Node_Object*);
    /* Node_Object* get_next(const Node_Object* self) */
    Node_Object* (*get_next)(const Node_Object*);
};

struct Node_Object {
    private_Node_Object p;
    impl_Node_Object* f;
};

TINYENGINE_API List_Object List_Object_new(void);
TINYENGINE_API Node_Object Node_Object_new(const Node_Object* prev, const Object* value, const Node_Object* next);