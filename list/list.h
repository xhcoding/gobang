#ifndef __list_h
#define __list_h
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct point {
    int x;
    int y;
}Point;


Point init_point(int x, int y);



#define CHECK_POINTER_NULL(pointer)				\
    do {							\
	if (pointer == NULL) {					\
	    fprintf(stderr, "List pointer must not be NULL\n");	\
	    exit(1);						\
	}							\
    } while(0)

#define CHECK_MALLOC(pointer, pointer_type)			\
    do{							\
	pointer = (pointer_type *)malloc(sizeof(pointer_type));		\
	if (pointer == NULL) {				\
	    fprintf(stderr, "memory malloc failed!");	\
	    exit(1);					\
	}						\
    }while(0)


typedef Point ValueType;

typedef struct _node{
    ValueType value;
    struct _node *front; // []--->[]
    struct _node *back; // []<---[]
} Node;

typedef struct _list {
    Node *head;
    Node *tail;
    size_t length;
} List;


typedef List Points;

/**
 * init list
 */

List* get_empty_list(void);

void push_back_list(List *list, ValueType v);

ValueType pop_back_list(List *list);

void push_front_list(List *list, ValueType v);

ValueType pop_front_list(List *list);

/**
 * push all of list2 into list1
 */
void append_back_list(List *list1, const List *list2);

/**
 * insert after pos
 */
void insert_list(List *list, Node *pos, ValueType v);


ValueType find_index_list(List *list, int index);

/**
 * make list be empty
 */
void clear_list(List *list);

void destroy_list(List *list);

int isEmpty(List *list);




#endif
