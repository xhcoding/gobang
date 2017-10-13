#include "list.h"

Point init_point(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

List* get_empty_list() {
    List *list = NULL;
    CHECK_MALLOC(list, List);
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}


void push_back_list(List *list, ValueType v) {
    CHECK_POINTER_NULL(list);

    Node *node = NULL;
    CHECK_MALLOC(node, Node);
    node->value = v;
    if (isEmpty(list)) {
	node->front = node->back = NULL;
	list->head = list->tail = node;
    } else {
	node->front = NULL;
	node->back = list->tail;
	list->tail->front = node;
	list->tail = node;
    }
    list->length++;
}


ValueType pop_back_list(List *list) {
    CHECK_POINTER_NULL(list);

    if (!isEmpty(list)) {
	ValueType tv = list->head->value;
	if (list->head == list->tail) {
	    free(list->head);
	    list->head = list->tail = NULL;
	} else {
	    Node *t = list->tail;
	    list->tail = list->tail->back;
	    list->tail->front = NULL;
	    free(t);
	}
	list->length--;
	return tv;
    }
    fprintf(stderr, "getting element error!");
    exit(1);
}

void push_front_list(List *list, ValueType v) {
    CHECK_POINTER_NULL(list);

    Node *node = NULL;
    CHECK_MALLOC(node, Node);
    node->value = v;
    if (isEmpty(list)) {
	node->front = node->back = NULL;
	list->head = list->tail = node;
    } else {
	node->back = NULL;
	node->front = list->head;
	list->head->back = node;
	list->head = node;
    }
    list->length++;
}

ValueType pop_front_list(List *list) {
    CHECK_POINTER_NULL(list);

    if (!isEmpty(list)) {
	ValueType tv = list->head->value;
	if (list->head == list->tail) {
	    free(list->head);
	    list->head = list->tail = NULL;
	} else {
	    Node *t = list->head;
	    list->head = list->head->front;
	    list->head->back = NULL;
	    free(t);
	}
	list->length--;
	return tv;
    }
    fprintf(stderr, "getting element error\n");
    exit(1);
}



void append_back_list(List *list1, const List *list2) {
    CHECK_POINTER_NULL(list1);
    CHECK_POINTER_NULL(list2);
    for (Node *node = list2->head; node != NULL; node = node->front) {
	push_back_list(list1, node->value);
    }
}

void insert_list(List *list, Node *pos, ValueType v) {
    CHECK_POINTER_NULL(list);
    CHECK_POINTER_NULL(pos);

    if (pos->front == NULL) {
	push_back_list(list, v);
    } else if (pos->back == NULL) {
	Node *node = NULL;
	CHECK_MALLOC(node, Node);

	node->front = pos->front;
	pos->front->back = node;
	node->back = pos;
	pos->front = node;
    }
    list->length++;
}



ValueType find_index_list(List *list, int index) {
    CHECK_POINTER_NULL(list);

    if (!isEmpty(list) && index >= 0 && index < list->length) {
	Node *node = list->head;
	for (int i = 0; i < index; i++) {
	    node = node->front;
	}
	return node->value;
    }

    fprintf(stderr, "getting element error\n");
    exit(1);
}


void clear_list(List *list) {
    CHECK_POINTER_NULL(list);

    for(Node *node = list->head;list->length != 0;list->length--) {
	Node *t = node;
	node = node->front;
	free(t);
    }
    list->head = list->tail = NULL;
}


void destroy_list(List *list) {
    CHECK_POINTER_NULL(list);
    clear_list(list);
    free(list);
    list = NULL;
}

int isEmpty(List *list) {
    CHECK_POINTER_NULL(list);
    return list->length == 0 ? 1 : 0;
}

