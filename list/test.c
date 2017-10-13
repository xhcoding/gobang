#include "list.h"
#include <stdio.h>
#include <string.h>


static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)		\
    do {								\
        test_count++;							\
        if (equality)							\
            test_pass++;						\
        else {								\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
            main_ret = 1;						\
        }								\
    } while(0)

#define EXPECT_EQ_STRING(expect, actual, alength)			\
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")

#define MAXLEN 1024
static char str[MAXLEN];

static void list2string(List *list, char *str, size_t maxlen) {
    Node *node = list->head;
    char t[100];
    memset(str, 0, MAXLEN);
    memset(t, 0, 100);
    for (int i = 0; i < list->length; i++) {
	snprintf(t, 100, "%d ", node->value);
	strcat(str, t);
	node = node->front;
    }
}

#ifdef VALUE_INT
static void test_insert_list() {
    List *list = get_empty_list();
    push_back_list(list, 1);
    push_back_list(list, 2);
    push_back_list(list, 3);
    push_back_list(list, 4);
    push_back_list(list, 5);
    list2string(list, str, MAXLEN);
    EXPECT_EQ_STRING("1 2 3 4 5 ", str, strlen(str));
    
    push_front_list(list, 0);
    push_front_list(list, -1);
    push_front_list(list, -2);
    push_front_list(list, -3);
    push_front_list(list, -4);
    push_front_list(list, -5);
    list2string(list, str, MAXLEN);
    EXPECT_EQ_STRING("-5 -4 -3 -2 -1 0 1 2 3 4 5 ", str, strlen(str));

    pop_back_list(list);
    list2string(list, str, MAXLEN);
    EXPECT_EQ_STRING("-5 -4 -3 -2 -1 0 1 2 3 4 ", str, strlen(str));

    pop_front_list(list);
    list2string(list, str, MAXLEN);
    EXPECT_EQ_STRING("-4 -3 -2 -1 0 1 2 3 4 ", str, strlen(str));

}

static void test_clear_list() {
    List *list = get_empty_list();
    push_back_list(list, 1);
    push_back_list(list, 2);
    push_back_list(list, 3);
    push_back_list(list, 4);
    push_back_list(list, 5);
    
    clear_list(list);
    list2string(list, str, MAXLEN);
    EXPECT_EQ_STRING("", str, strlen(str));

}

void test_list(void) {
    test_insert_list();
    test_clear_list();
}

#endif

int main() {

    // test_list();
    
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    
    return 0;
    
}
