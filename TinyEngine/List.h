#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "TinyEngine.h"
#include "Box.h"

#define declexp_List(T, declname) \
 \
struct private_List_##declname; \
typedef struct private_List_##declname private_List_##declname; \
 \
struct impl_List_##declname; \
typedef struct impl_List_##declname impl_List_##declname; \
 \
struct List_##declname; \
typedef struct List_##declname List_##declname; \
 \
struct private_Node_##declname; \
typedef struct private_Node_##declname private_Node_##declname; \
 \
struct impl_Node_##declname; \
typedef struct impl_Node_##declname impl_Node_##declname; \
 \
struct Node_##declname; \
typedef struct Node_##declname Node_##declname; \
 \
struct private_List_##declname { \
    int length; \
    Node_##declname* first; \
    Node_##declname* last; \
}; \
 \
struct impl_List_##declname { \
    /* void clear(const List_##declname* self, void (*disposefn)(const T)) */ \
    void (*clear)(List_##declname*, void (*)(const T)); \
    /* int get_length(const List_##declname* self) */ \
    int (*get_length)(const List_##declname*); \
    /* bool is_empty(const List_##declname* self) */ \
    bool (*is_empty)(const List_##declname*); \
 \
    /* T get_front(const List_##declname* self) */ \
    T (*get_front)(const List_##declname*); \
    /* Node_##declname* push_front(List_##declname* self, const T value) */ \
    Node_##declname* (*push_front)(List_##declname*, const T); \
    /* void pop_front(List_##declname* self, void (*disposefn)(const T)) */ \
    void (*pop_front)(List_##declname*, void (*)(const T)); \
    /* T get_back(const List_##declname* self) */ \
    T (*get_back)(const List_##declname*); \
    /* Node_##declname* push_back(List_##declname* self, const T value) */ \
    Node_##declname* (*push_back)(List_##declname*, const T); \
    /* void pop_back(List_##declnamet* self, void (*disposefn)(const T)) */ \
    void (*pop_back)(List_##declname*, void (*)(const T)); \
 \
    /* Node_##declname* insert(List_##declname* self, const Node_##declname* pos, const T value) */ \
    Node_##declname* (*insert)(List_##declname*, const Node_##declname*, const T); \
    /* void remove(List_##declname* self, const Node_##declname* pos, void (*disposefn)(const T)) */ \
    void (*remove)(List_##declname*, const Node_##declname*, void (*)(const T)); \
    /* T find(const List_##declname* self, const T value) */ \
    T (*find)(const List_##declname*, const T); \
    /* T find_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)) */ \
    T (*find_by)(const List_##declname*, const T); \
    /* bool contains(const List_##declname* self, const T value) */ \
    bool (*contains)(const List_##declname*, const T); \
    /* bool contains_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)) */ \
    bool (*contains_by)(const List_##declname*, const T, bool (*)(const T, const T)); \
    /* void for_each(const List_##declnamet* self, void (*fn)(const T)) lambda*/ \
    void (*for_each)(const List_##declname*, void (*)(const T)); \
}; \
 \
struct List_##declname { \
    private_List_##declname p; \
    impl_List_##declname* f; \
}; \
 \
struct private_Node_##declname { \
    \
    Node_##declname* prev; \
    T value; \
    Node_##declname* next; \
}; \
 \
struct impl_Node_##declname { \
    /* Node_##declname* get_prev(const Node_##declname* self) */ \
    Node_##declname* (*get_prev)(const Node_##declname*); \
    /* Node_##declname* get_next(const Node_##declname* self) */ \
    Node_##declname* (*get_next)(const Node_##declname*); \
}; \
 \
struct Node_##declname { \
    private_Node_##declname p; \
    impl_Node_##declname* f; \
}; \
 \
TINYENGINE_API List_##declname List_##declname##_new(void); \
TINYENGINE_API Node_##declname Node_##declname##_new(const Node_##declname* prev, const T value, const Node_##declname* next);


#define decl_List(T, declname) \
 \
struct private_List_##declname; \
typedef struct private_List_##declname private_List_##declname; \
 \
struct impl_List_##declname; \
typedef struct impl_List_##declname impl_List_##declname; \
 \
struct List_##declname; \
typedef struct List_##declname List_##declname; \
 \
struct private_Node_##declname; \
typedef struct private_Node_##declname private_Node_##declname; \
 \
struct impl_Node_##declname; \
typedef struct impl_Node_##declname impl_Node_##declname; \
 \
struct Node_##declname; \
typedef struct Node_##declname Node_##declname; \
 \
struct private_List_##declname { \
    int length; \
    Node_##declname* first; \
    Node_##declname* last; \
}; \
 \
struct impl_List_##declname { \
    /* void clear(const List_##declname* self, void (*disposefn)(const T)) */ \
    void (*clear)(List_##declname*, void (*)(const T)); \
    /* int get_length(const List_##declname* self) */ \
    int (*get_length)(const List_##declname*); \
    /* bool is_empty(const List_##declname* self) */ \
    bool (*is_empty)(const List_##declname*); \
 \
    /* T get_front(const List_##declname* self) */ \
    T (*get_front)(const List_##declname*); \
    /* Node_##declname* push_front(List_##declname* self, const T value) */ \
    Node_##declname* (*push_front)(List_##declname*, const T); \
    /* void pop_front(List_##declname* self, void (*disposefn)(const T)) */ \
    void (*pop_front)(List_##declname*, void (*)(const T)); \
    /* T get_back(const List_##declname* self) */ \
    T (*get_back)(const List_##declname*); \
    /* Node_##declname* push_back(List_##declname* self, const T value) */ \
    Node_##declname* (*push_back)(List_##declname*, const T); \
    /* void pop_back(List_##declnamet* self, void (*disposefn)(const T)) */ \
    void (*pop_back)(List_##declname*, void (*)(const T)); \
 \
    /* Node_##declname* insert(List_##declname* self, const Node_##declname* pos, const T value) */ \
    Node_##declname* (*insert)(List_##declname*, const Node_##declname*, const T); \
    /* void remove(List_##declname* self, const Node_##declname* pos, void (*disposefn)(const T)) */ \
    void (*remove)(List_##declname*, const Node_##declname*, void (*)(const T)); \
    /* T find(const List_##declname* self, const T value) */ \
    T (*find)(const List_##declname*, const T); \
    /* T find_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)) */ \
    T (*find_by)(const List_##declname*, const T); \
    /* bool contains(const List_##declname* self, const T value) */ \
    bool (*contains)(const List_##declname*, const T); \
    /* bool contains_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)) */ \
    bool (*contains_by)(const List_##declname*, const T, bool (*)(const T, const T)); \
    /* void for_each(const List_##declnamet* self, void (*fn)(const T)) lambda*/ \
    void (*for_each)(const List_##declname*, void (*)(const T)); \
}; \
 \
struct List_##declname { \
    private_List_##declname p; \
    impl_List_##declname* f; \
}; \
 \
struct private_Node_##declname { \
    \
    Node_##declname* prev; \
    T value; \
    Node_##declname* next; \
}; \
 \
struct impl_Node_##declname { \
    /* Node_##declname* get_prev(const Node_##declname* self) */ \
    Node_##declname* (*get_prev)(const Node_##declname*); \
    /* Node_##declname* get_next(const Node_##declname* self) */ \
    Node_##declname* (*get_next)(const Node_##declname*); \
}; \
 \
struct Node_##declname { \
    private_Node_##declname p; \
    impl_Node_##declname* f; \
}; \
 \
List_##declname List_##declname##_new(void); \
Node_##declname Node_##declname##_new(const Node_##declname* prev, const T value, const Node_##declname* next);


#define def_List(T, declname) \
 \
/*list decl*/ \
 \
static void List_##declname##_clear(const List_##declname* self); \
static int List_##declname##_get_length(const List_##declname* self); \
static bool List_##declname##_is_empty(const List_##declname* self); \
 \
static T List_##declname##_get_front(const List_##declname* self); \
static Node_##declname* List_##declname##_push_front(List_##declname* self, const T value); \
static void List_##declname##_pop_front(List_##declname* self, void (*disposefn)(const T)); \
static T List_##declname##_get_back(const List_##declname* self); \
static Node_##declname* List_##declname##_push_back(List_##declname* self, const T value); \
static void List_##declname##_pop_back(List_##declname* self, void (*disposefn)(const T)); \
 \
static Node_##declname* List_##declname##_insert(List_##declname* self, const Node_##declname* pos, const T value); \
static void List_##declname##_remove(List_##declname* self, const Node_##declname* pos, void (*disposefn)(const T)); \
static T List_##declname##_find(const List_##declname* self, const T value); \
static T List_##declname##_find_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)); \
static bool List_##declname##_contains(const List_##declname* self, const T value); \
static bool List_##declname##_contains_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)); \
static void List_##declname##_for_each(const List_##declname* self, void (*fn)(const T)); \
 \
 \
/*node decl*/ \
 \
static Node_##declname* Node_##declname##_get_prev(const Node_##declname* self); \
static Node_##declname* Node_##declname##_get_next(const Node_##declname* self); \
 \
impl_List_##declname impl_List_##declname##_table = { \
		.clear = List_##declname##_clear, \
		.get_length = List_##declname##_get_length, \
		.is_empty = List_##declname##_is_empty, \
 \
		.get_front = List_##declname##_get_front, \
		.push_front = List_##declname##_push_front, \
		.pop_front = List_##declname##_pop_front, \
		.get_back = List_##declname##_get_back, \
		.push_back = List_##declname##_push_back, \
		.pop_back = List_##declname##_pop_back, \
 \
		.insert = List_##declname##_insert, \
		.remove = List_##declname##_remove, \
		.find = List_##declname##_find, \
		.find_by = List_##declname##_find_by, \
		.contains = List_##declname##_contains, \
		.contains_by = List_##declname##_find_by, \
		.for_each = List_##declname##_for_each \
}; \
 \
List_##declname List_##declname##_new(void) { \
	private_List_##declname p_instance = { \
		.length = 0, \
		.first = NULL, \
		.last = NULL \
	}; \
 \
	List_##declname instance = { \
		.p = p_instance, \
		.f = &impl_List_##declname##_table \
	}; \
 \
	return instance; \
} \
 \
impl_Node_##declname impl_Node_##declname##_table = { \
		.get_prev = Node_##declname##_get_prev, \
		.get_next = Node_##declname##_get_next \
}; \
 \
Node_##declname Node_##declname##_new(const Node_##declname* prev, const T value, const Node_##declname* next) { \
	private_Node_##declname p_instance = { \
		.prev = prev, \
		.value = value, \
		.next = next \
	}; \
 \
	Node_##declname instance = { \
		.p = p_instance, \
		.f = &impl_Node_##declname##_table \
	}; \
 \
	return instance; \
} \
 \
/*list def*/ \
 \
static void List_##declname##_clear(const List_##declname* self, void (*disposefn)(const T)) { \
	assert(self != NULL); \
	while (self->p.first != NULL) \
		List_##declname##_pop_front(self, disposefn); \
} \
 \
static int List_##declname##_get_length(const List_##declname* self) { \
	assert(self != NULL); \
	return self->p.length; \
} \
 \
static bool List_##declname##_is_empty(const List_##declname* self) { \
	assert(self != NULL); \
	return self->p.first != NULL; \
} \
 \
 \
static T List_##declname##_get_front(const List_##declname* self) { \
	assert(self != NULL); \
	if (self->p.first == NULL) \
		return NULL; \
	return self->p.first->p.value; \
} \
 \
static Node_##declname* List_##declname##_push_front(List_##declname* self, const T value) { \
	assert(self != NULL); \
	Node_##declname instance = Node_##declname##_new(NULL, value, self->p.first); \
	box(Node_Object, instance) \
		self->p.first = instance_boxed; \
	self->p.length += 1; \
	if (self->p.first->p.next != NULL) \
		self->p.first->p.next->p.prev = instance_boxed; \
	if (self->p.last == NULL) \
		self->p.last = self->p.first; \
	return instance_boxed; \
} \
 \
static void List_##declname##_pop_front(List_##declname* self, void (*disposefn)(const T)) { \
	assert(self != NULL); \
	Node_##declname* temp = self->p.first; \
	if (self->p.first->p.next != NULL) { \
		self->p.first = self->p.first->p.next; \
		self->p.first->p.prev = NULL; \
	} \
	else { \
		self->p.first = NULL; \
		self->p.last = NULL; \
	} \
	if (disposefn != NULL) \
		disposefn(temp->p.value); \
	free(temp); \
	self->p.length -= 1; \
} \
 \
static T List_##declname##_get_back(const List_##declname* self) { \
	assert(self != NULL); \
	if (self->p.last == NULL) \
		return NULL; \
	return self->p.last->p.value; \
} \
 \
static Node_##declname* List_##declname##_push_back(List_##declname* self, const T value) { \
	assert(self != NULL); \
	Node_##declname instance = Node_##declname##_new(self->p.last, value, NULL); \
	box(Node_Object, instance) \
		self->p.last = instance_boxed; \
	self->p.length += 1; \
	if (self->p.last->p.prev != NULL) \
		self->p.last->p.prev->p.next = instance_boxed; \
	if (self->p.first == NULL) \
		self->p.first = self->p.last; \
	return instance_boxed; \
} \
 \
static void List_##declname##_pop_back(List_##declname* self, void (*disposefn)(const T)) { \
	assert(self != NULL); \
	Node_##declname* temp = self->p.last; \
	if (self->p.last->p.prev != NULL) { \
		self->p.last = self->p.last->p.prev; \
		self->p.last->p.next = NULL; \
	} \
	else { \
		self->p.first = NULL; \
		self->p.last = NULL; \
	} \
	if (disposefn != NULL) \
		disposefn(temp->p.value); \
	free(temp); \
	self->p.length -= 1; \
} \
 \
 \
static Node_##declname* List_##declname##_insert(List_##declname* self, const Node_##declname* pos, const T value) { \
	assert(self != NULL); \
	assert(pos != NULL); \
	Node_##declname instance = Node_##declname##_new(pos->p.prev, value, pos); \
	box(Node_Object, instance) \
		if (pos->p.prev != NULL) \
			pos->p.prev->p.next = instance_boxed; \
	if (pos->p.next != NULL) \
		pos->p.next->p.prev = instance_boxed; \
	self->p.length += 1; \
	return instance_boxed; \
} \
 \
static void List_##declname##_remove(List_##declname* self, const Node_##declname* pos, void (*disposefn)(const T)) { \
	assert(self != NULL); \
	assert(pos != NULL); \
	Node_##declname* prev = pos->p.prev; \
	Node_##declname* curr = pos; \
	Node_##declname* next = pos->p.next; \
 \
	if (prev != NULL) \
		prev->p.next = next; \
	else \
		self->p.first = next; \
	if (next != NULL) \
		next->p.prev = prev; \
	else \
		self->p.last = prev; \
 \
	if (disposefn != NULL) \
		disposefn(curr->p.value); \
	free(curr); \
	self->p.length -= 1; \
} \
 \
static T List_##declname##_find(const List_##declname* self, const T value) { \
	assert(self != NULL); \
	assert(value != NULL); \
	const Node_##declname* index = self->p.first; \
	while (index != NULL) \
	{ \
		if (index->p.value == value) \
			return index->p.value; \
		index = index->p.next; \
	} \
	return NULL; \
} \
 \
static T List_##declname##_find_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)) { \
	assert(self != NULL); \
	assert(value != NULL); \
	const Node_##declname* index = self->p.first; \
	while (index != NULL) \
	{ \
		if (comparer(index->p.value, value)) \
			return index->p.value; \
		index = index->p.next; \
	} \
	return NULL; \
} \
 \
static bool List_##declname##_contains(const List_##declname* self, const T value) { \
	assert(self != NULL); \
	assert(value != NULL); \
	const Node_##declname* index = self->p.first; \
	while (index != NULL) \
	{ \
		if (index->p.value == value) \
			return true; \
		index = index->p.next; \
	} \
	return false; \
} \
 \
static bool List_##declname##_contains_by(const List_##declname* self, const T value, bool (*comparer)(const T, const T)) { \
	assert(self != NULL); \
	assert(value != NULL); \
	const Node_##declname* index = self->p.first; \
	while (index != NULL) \
	{ \
		if (comparer(index->p.value, value)) \
			return true; \
		index = index->p.next; \
	} \
	return false; \
} \
 \
static void List_##declname##_for_each(const List_##declname* self, void (*fn)(const T)) { \
	assert(self != NULL); \
	assert(fn != NULL); \
	Node_##declname* index = self->p.first; \
	while (index != NULL) \
	{ \
		fn(index->p.value); \
		index = index->p.next; \
	} \
} \
 \
/*node def*/ \
 \
static Node_##declname* Node_##declname##_get_prev(const Node_##declname* self) { \
	return self->p.prev; \
} \
 \
static Node_##declname* Node_##declname##_get_next(const Node_##declname* self) { \
	return self->p.next; \
}