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
    void (*clear)(List_Object* self, void (*disposefn)(const Object*));
    int (*get_length)(const List_Object* self);
    bool (*is_empty)(const List_Object* self);

    Object* (*get_front)(const List_Object* self);
    Node_Object* (*push_front)(List_Object* self, Object* value);
    void (*pop_front)(List_Object* self, void (*disposefn)(const Object*));
    Object* (*get_back)(const List_Object* self);
    Node_Object* (*push_back)(List_Object* self, Object* value);
    void (*pop_back)(List_Object* self, void (*disposefn)(const Object*));

    Node_Object* (*insert)(List_Object* self, Node_Object* pos, Object* value);
    void (*remove)(List_Object* self, Node_Object* pos, void (*disposefn)(const Object*));
    Object* (*find)(const List_Object* self, const Object* value);
    Object* (*find_by)(const List_Object* self, const Object* value, bool (*comparer)(const Object*, const Object*));
    bool (*contains)(const List_Object* self, const Object* value);
    bool (*contains_by)(const List_Object* self, const Object* value, bool (*comparer)(const Object*, const Object*)); 
    void (*for_each)(const List_Object* self, void (*fn)(const Object*));
};

struct List_Object {
    private_List_Object p;
    const impl_List_Object* const f;
};

struct private_Node_Object {
    Node_Object* prev;
    Object* value;
    Node_Object* next;
};

struct impl_Node_Object {
    Node_Object* (*get_prev)(const Node_Object* self);
    Node_Object* (*get_next)(const Node_Object* self);
};

struct Node_Object {
    private_Node_Object p;
    const impl_Node_Object* const f;
};

TINYENGINE_API List_Object List_Object_new(void);
TINYENGINE_API Node_Object Node_Object_new(Node_Object* prev, Object* value, Node_Object* next);