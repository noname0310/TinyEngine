#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "TinyEngine.h"
#include "OOPTool.h"

//TODO: re write static_table, struct macro, premitive_macro

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
    void (*const dispose)(List_##declname* self, void (*disposefn)(const T)); \
    void (*const clear)(List_##declname* self, void (*disposefn)(const T)); \
    int (*const get_length)(const List_##declname* self); \
    bool (*const is_empty)(const List_##declname* self); \
 \
    T (*const get_front)(const List_##declname* self); \
    Node_##declname* (*const push_front)(List_##declname* self, T value); \
    void (*const pop_front)(List_##declname* self, void (*disposefn)(const T)); \
    T (*const get_back)(const List_##declname* self); \
    Node_##declname* (*const push_back)(List_##declname* self, T value); \
    void (*const pop_back)(List_##declname* self, void (*disposefn)(const T)); \
 \
    Node_##declname* (*const insert)(List_##declname* self, const Node_##declname* pos, const T value); \
    void (*const remove)(List_##declname* self, Node_##declname* pos, void (*disposefn)(const T)); \
    T (*const find)(const List_##declname* self, const T value); \
    T (*const find_by)(const List_##declname* self, const T value, bool (*comparer)(const T, const T)); \
    bool (*const contains)(const List_##declname* self, const T value); \
    bool (*const contains_by)(const List_##declname* self, const T value, bool (*comparer)(const T, const T)); \
    void (*const for_each)(const List_##declname* self, void (*fn)(const T)); \
}; \
 \
struct List_##declname { \
    private_List_##declname p; \
    const impl_List_##declname* const f; \
}; \
 \
struct private_Node_##declname { \
    Node_##declname* prev; \
    T value; \
    Node_##declname* next; \
}; \
 \
struct impl_Node_##declname { \
    Node_##declname* (*const get_prev)(const Node_##declname* self); \
    Node_##declname* (*const get_next)(const Node_##declname* self); \
}; \
 \
struct Node_##declname { \
    private_Node_##declname p; \
    const impl_Node_##declname* const f; \
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
    void (*const dispose)(List_##declname* self, void (*disposefn)(const T)); \
    void (*const clear)(List_##declname* self, void (*disposefn)(const T)); \
    int (*const get_length)(const List_##declname* self); \
    bool (*const is_empty)(const List_##declname* self); \
 \
    T (*const get_front)(const List_##declname* self); \
    Node_##declname* (*const push_front)(List_##declname* self, T value); \
    void (*const pop_front)(List_##declname* self, void (*disposefn)(const T)); \
    T (*const get_back)(const List_##declname* self); \
    Node_##declname* (*const push_back)(List_##declname* self, T value); \
    void (*const pop_back)(List_##declname* self, void (*disposefn)(const T)); \
 \
    Node_##declname* (*const insert)(List_##declname* self, const Node_##declname* pos, const T value); \
    void (*const remove)(List_##declname* self, Node_##declname* pos, void (*disposefn)(const T)); \
    T (*const find)(const List_##declname* self, const T value); \
    T (*const find_by)(const List_##declname* self, const T value, bool (*comparer)(const T, const T)); \
    bool (*const contains)(const List_##declname* self, const T value); \
    bool (*const contains_by)(const List_##declname* self, const T value, bool (*comparer)(const T, const T)); \
    void (*const for_each)(const List_##declname* self, void (*fn)(const T)); \
}; \
 \
struct List_##declname { \
    private_List_##declname p; \
    const impl_List_##declname* const f; \
}; \
 \
struct private_Node_##declname { \
    Node_##declname* prev; \
    T value; \
    Node_##declname* next; \
}; \
 \
struct impl_Node_##declname { \
    Node_##declname* (*const get_prev)(const Node_##declname* self); \
    Node_##declname* (*const get_next)(const Node_##declname* self); \
}; \
 \
struct Node_##declname { \
    private_Node_##declname p; \
    const impl_Node_##declname* const f; \
}; \
 \
List_##declname List_##declname##_new(void); \
Node_##declname Node_##declname##_new(const Node_##declname* prev, const T value, const Node_##declname* next);


#define def_List(T, declname) \
 \
/*list decl*/ \
 \
static void List_##declname##_dispose(List_##declname* self, void (*disposefn)(const T)); \
static void List_##declname##_clear(List_##declname* self, void (*disposefn)(const T)); \
static int List_##declname##_get_length(const List_##declname* self); \
static bool List_##declname##_is_empty(const List_##declname* self); \
 \
static T List_##declname##_get_front(const List_##declname* self); \
static Node_##declname* List_##declname##_push_front(List_##declname* self, T value); \
static void List_##declname##_pop_front(List_##declname* self, void (*disposefn)(const T)); \
static T List_##declname##_get_back(const List_##declname* self); \
static Node_##declname* List_##declname##_push_back(List_##declname* self, T value); \
static void List_##declname##_pop_back(List_##declname* self, void (*disposefn)(const T)); \
 \
static Node_##declname* List_##declname##_insert(List_##declname* self, const Node_##declname* pos, const T value); \
static void List_##declname##_remove(List_##declname* self, Node_##declname* pos, void (*disposefn)(const T)); \
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
const impl_List_##declname impl_List_##declname##_table = { \
		.dispose = List_##declname##_dispose, \
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
		.contains_by = List_##declname##_contains_by, \
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
static void List_##declname##_dispose(List_##declname* self, void (*disposefn)(const T)) { \
	List_##declname##_clear(self, disposefn); \
} \
 \
static void List_##declname##_clear(List_##declname* self, void (*disposefn)(const T)) { \
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
static Node_##declname* List_##declname##_push_front(List_##declname* self, T value) { \
	assert(self != NULL); \
	Node_##declname instance = Node_##declname##_new(NULL, value, self->p.first); \
	box(Node_##declname, instance) \
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
static Node_##declname* List_##declname##_push_back(List_##declname* self, T value) { \
	assert(self != NULL); \
	Node_##declname instance = Node_##declname##_new(self->p.last, value, NULL); \
	box(Node_##declname, instance) \
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
	box(Node_##declname, instance) \
		if (pos->p.prev != NULL) \
			pos->p.prev->p.next = instance_boxed; \
	if (pos->p.next != NULL) \
		pos->p.next->p.prev = instance_boxed; \
	self->p.length += 1; \
	return instance_boxed; \
} \
 \
static void List_##declname##_remove(List_##declname* self, Node_##declname* pos, void (*disposefn)(const T)) { \
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
