#include "pch.h" //for test
#include "ObjectListSample.h"

/*list decl*/

static void List_Object_dispose(List_Object* self, void (*disposefn)(const Object self));
static void List_Object_clear(List_Object* self, void (*disposefn)(const Object self));
static int List_Object_get_length(const List_Object* self);
static bool List_Object_is_empty(const List_Object* self);

static Object* List_Object_get_front(const List_Object* self);
static Node_Object* List_Object_push_front(List_Object* self, Object value);
static void List_Object_pop_front(List_Object* self, void (*disposefn)(const Object self));
static Object* List_Object_get_back(const List_Object* self);
static Node_Object* List_Object_push_back(List_Object* self, Object value);
static void List_Object_pop_back(List_Object* self, void (*disposefn)(const Object self));

static Node_Object* List_Object_insert(List_Object* self, Node_Object* pos, Object value);
static void List_Object_remove(List_Object* self, Node_Object* pos, void (*disposefn)(const Object self));
static Object* List_Object_unsafe_find(const List_Object* self, const Object value);
static Object* List_Object_find_by(const List_Object* self, const Object value, bool (*comparer)(const Object lhs, const Object rhs));
static bool List_Object_unsafe_contains(const List_Object* self, const Object value);
static bool List_Object_contains_by(const List_Object* self, const Object value, bool (*comparer)(const Object lhs, const Object rhs));
static void List_Object_c_for_each(const List_Object* self, void (*fn)(const Object item));
static void List_Object_for_each(const List_Object* self, void (*fn)(const Object* item));


/*node decl*/

static Node_Object* Node_Object_get_prev(const Node_Object* self);
static Node_Object* Node_Object_get_next(const Node_Object* self);

const impl_List_Object impl_List_Object_table = {
	.dispose = List_Object_dispose,
	.clear = List_Object_clear,
	.get_length = List_Object_get_length,
	.is_empty = List_Object_is_empty,

	.get_front = List_Object_get_front,
	.push_front = List_Object_push_front,
	.pop_front = List_Object_pop_front,
	.get_back = List_Object_get_back,
	.push_back = List_Object_push_back,
	.pop_back = List_Object_pop_back,

	.insert = List_Object_insert,
	.remove = List_Object_remove,
	.unsafe_find = List_Object_unsafe_find,
	.find_by = List_Object_find_by,
	.unsafe_contains = List_Object_unsafe_contains,
	.contains_by = List_Object_contains_by,
	.c_for_each = List_Object_c_for_each,
	.for_each = List_Object_for_each
};

List_Object List_Object_new(void) {
	private_List_Object p_instance = {
		.length = 0,
		.first = NULL,
		.last = NULL
	};

	List_Object instance = {
		.f = &impl_List_Object_table,
		.p = p_instance
	};

	return instance;
}

impl_Node_Object impl_Node_Object_table = {
		.get_prev = Node_Object_get_prev,
		.get_next = Node_Object_get_next
};

Node_Object Node_Object_new(Node_Object* prev, Object value, Node_Object* next) {
	private_Node_Object p_instance = {
		.prev = prev,
		.value = value,
		.next = next
	};

	Node_Object instance = {
		.f = &impl_Node_Object_table,
		.p = p_instance
	};

	return instance;
}

/*list def*/

static void List_Object_dispose(List_Object* self, void (*disposefn)(const Object self)) {
	List_Object_clear(self, disposefn);
}

static void List_Object_clear(List_Object* self, void (*disposefn)(const Object self)) {
	assert(self != NULL);
	while (self->p.first != NULL)
		List_Object_pop_front(self, disposefn);
}

static int List_Object_get_length(const List_Object* self) {
	assert(self != NULL);
	return self->p.length;
}

static bool List_Object_is_empty(const List_Object* self) {
	assert(self != NULL);
	return self->p.first != NULL;
}


static Object* List_Object_get_front(const List_Object* self) {
	assert(self != NULL);
	if (self->p.first == NULL)
		return NULL;
	return &(self->p.first->p.value);
}

static Node_Object* List_Object_push_front(List_Object* self, Object value) {
	assert(self != NULL);
	Node_Object instance = Node_Object_new(NULL, value, self->p.first);
	box(Node_Object, instance)
	self->p.first = instance_boxed;
	self->p.length += 1;
	if (self->p.first->p.next != NULL)
		self->p.first->p.next->p.prev = instance_boxed;
	if (self->p.last == NULL)
		self->p.last = self->p.first;
	return instance_boxed;
}

static void List_Object_pop_front(List_Object* self, void (*disposefn)(const Object self)) {
	assert(self != NULL);
	Node_Object* temp = self->p.first;
	if (self->p.first->p.next != NULL) {
		self->p.first = self->p.first->p.next;
		self->p.first->p.prev = NULL;
	} else {
		self->p.first = NULL;
		self->p.last = NULL;
	}
	if (disposefn != NULL)
		disposefn(temp->p.value);
	free(temp);
	self->p.length -= 1;
}

static Object* List_Object_get_back(const List_Object* self) {
	assert(self != NULL);
	if (self->p.last == NULL)
		return NULL;
	return &(self->p.last->p.value);
}

static Node_Object* List_Object_push_back(List_Object* self, Object value) {
	assert(self != NULL);
	Node_Object instance = Node_Object_new(self->p.last, value, NULL);
	box(Node_Object, instance)
	self->p.last = instance_boxed;
	self->p.length += 1;
	if (self->p.last->p.prev != NULL)
		self->p.last->p.prev->p.next = instance_boxed;
	if (self->p.first == NULL)
		self->p.first = self->p.last;
	return instance_boxed;
}

static void List_Object_pop_back(List_Object* self, void (*disposefn)(const Object self)) {
	assert(self != NULL);
	Node_Object* temp = self->p.last;
	if (self->p.last->p.prev != NULL) {
		self->p.last = self->p.last->p.prev;
		self->p.last->p.next = NULL;
	} else {
		self->p.first = NULL;
		self->p.last = NULL;
	}
	if (disposefn != NULL)
		disposefn(temp->p.value);
	free(temp);
	self->p.length -= 1;
}


static Node_Object* List_Object_insert(List_Object* self, Node_Object* pos, Object value) {
	//todo: need to fix
	if (self->p.first == pos)
		return List_Object_push_front(self, value);
	//
	assert(self != NULL);
	assert(pos != NULL);
	Node_Object instance = Node_Object_new(pos->p.prev, value, pos);
	box(Node_Object, instance)
	if (pos->p.prev != NULL)
		pos->p.prev->p.next = instance_boxed;
	if (pos->p.next != NULL)
		pos->p.next->p.prev = instance_boxed;
	self->p.length += 1;
	return instance_boxed;
}

static void List_Object_remove(List_Object* self, Node_Object* pos, void (*disposefn)(const Object self)) {
	assert(self != NULL);
	assert(pos != NULL);
	Node_Object* prev = pos->p.prev;
	Node_Object* curr = pos;
	Node_Object* next = pos->p.next;

	if (prev != NULL)
		prev->p.next = next;
	else
		self->p.first = next;
	if (next != NULL)
		next->p.prev = prev;
	else
		self->p.last = prev;

	if (disposefn != NULL)
		disposefn(curr->p.value);
	free(curr);
	self->p.length -= 1;
}

static Object* List_Object_unsafe_find(const List_Object* self, const Object value) {
	assert(self != NULL);
	const Node_Object* index = self->p.first;
	while (index != NULL) {
		if (memcmp(&(index->p.value), &value, sizeof(Object)) == 0)
			return (Object*)&(index->p.value);
		index = index->p.next;
	}
	return NULL;
}

static Object* List_Object_find_by(const List_Object* self, const Object value, bool (*comparer)(const Object lhs, const Object rhs)) {
	assert(self != NULL);
	const Node_Object* index = self->p.first;
	while (index != NULL) {
		if (comparer(index->p.value, value))
			return (Object*)&(index->p.value);
		index = index->p.next;
	}
	return NULL;
}

static bool List_Object_unsafe_contains(const List_Object* self, const Object value) {
	assert(self != NULL);
	const Node_Object* index = self->p.first;
	while (index != NULL) {
		if (memcmp(&(index->p.value), &value, sizeof(Object)) == 0)
			return true;
		index = index->p.next;
	}
	return false;
}

static bool List_Object_contains_by(const List_Object* self, const Object value, bool (*comparer)(const Object lhs, const Object rhs)) {
	assert(self != NULL);
	const Node_Object* index = self->p.first;
	while (index != NULL) {
		if (comparer(index->p.value, value))
			return true;
		index = index->p.next;
	}
	return false;
}

static void List_Object_c_for_each(const List_Object* self, void (*fn)(const Object item)) {
	assert(self != NULL);
	assert(fn != NULL);
	Node_Object* index = self->p.first;
	while (index != NULL) {
		fn(index->p.value);
		index = index->p.next;
	}
}

static void List_Object_for_each(const List_Object* self, void (*fn)(const Object* item)) {
	assert(self != NULL);
	assert(fn != NULL);
	Node_Object* index = self->p.first;
	while (index != NULL) {
		fn(&(index->p.value));
		index = index->p.next;
	}
}

/*node def*/

static Node_Object* Node_Object_get_prev(const Node_Object* self) {
	return self->p.prev;
}

static Node_Object* Node_Object_get_next(const Node_Object* self) {
	return self->p.next;
}