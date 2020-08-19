#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "TinyEngine.h"
#include "Object.h"

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
    Node_Object* tail;
};

struct impl_List_Object {
    /* void clear(const List_Object* self) */
    void (*clear)(List_Object*);
    /* int get_length(const List_Object* self) */
    int (*get_length)(const List_Object*);
    /* bool is_empty(const List_Object* self) */
    bool (*is_empty)(const List_Object*);

    /* Object get_front(const List_Object* self) */
    Object(*get_front)(const List_Object*);
    /* Object get_front_ptr(const List_Object* self) */
    Object* (*get_front_ptr)(const List_Object*);
    /* void push_front(const List_Object* self, const Object value) */
    void (*push_front)(const List_Object*, const Object*);
    /* void pop_front(const List_Object* self) */
    void (*pop_front)(const List_Object*);

    /* Object get_back(const List_Object* self) */
    Object(*get_back)(const List_Object*);
    /* Object get_back_ptr(const List_Object* self) */
    Object* (*get_back_ptr)(const List_Object*);
    /* void push_back(const List_Object* self, const Object value) */
    void (*push_back)(const List_Object*, const Object*);
    /* void pop_back(const List_Object* self) */
    void (*pop_back)(const List_Object*);

    Node_Object (*insert)(const List_Object*, const Node_Object*, const Object*);
    Node_Object (*erase)(const List_Object*, const Node_Object*);

    void (*remove)(List_Object*, type);
    void (*remove_by)(List_Object*, bool (*)(const type*));

    Node_Object (*begin)(List_Object*);
    Node_Object (*end)(List_Object*);

    Node_Object (*find)(const List_Object*, const type);
    Node_Object (*find_by)(const List_Object*, bool (*)(const type*));

    bool (*contains)(const List_Object*, const type*);
    bool (*contains_by)(const List_Object*, bool (*)(const type*));

    void (*for_each)(const List_Object*, void (*)(type));
    void (*for_each_ptr)(const List_Object*, void (*)(type*));
    void (*for_each_cptr)(const List_Object*, void (*)(const type*));
};

struct List_Object {
    private_List_Object p;
    impl_List_Object* f;
};

struct private_Node_Object {
    Node_Object* prev;
    Object value;
    Node_Object* next;
};

struct impl_Node_Object {
    Node_Object* (*prev)(const Node_Object*);
    Node_Object* (*next)(const Node_Object*);
};

struct Node_Object {
    private_Node_Object p;
    impl_Node_Object* f;
};

TINYENGINE_API Node_Object Node_Object_new(Object*);