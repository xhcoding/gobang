#include "gobang.h"
#include "list/list.h"

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



#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")



static void testHasNeighbors(Board *board) {
    // distance = 1, count = 1
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(7, 9), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 10), 1, 1)); 
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 11), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(7, 6), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 5), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 4), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(6, 6), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(6, 7), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(6, 8), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(6, 9), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(6, 5), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(6, 10), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(8, 6), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(8, 7), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(8, 8), 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(8, 9), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(8, 5), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(8, 10), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(5, 7), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(5, 8), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(9, 7), 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(9, 8), 1, 1));

    // distance = 2, count = 2
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 10), 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 11), 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 5), 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(7, 4), 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(6, 5), 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(6, 10), 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(8, 5), 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, init_point(8, 10), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(5, 6), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(5, 7), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(5, 8), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(5, 9), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(9, 6), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(9, 7), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(9, 8), 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, init_point(9, 9), 2, 2));
    
 
}

static void testGen(Board *board) {
    List *points = gen(board, 6);
    EXPECT_EQ_INT(18, (int)points->length);
}

static void testEvaluate_Point(Board *board) {
    EXPECT_EQ_INT(31, evaluate_point(board, init_point(7, 9), BLACK));
    EXPECT_EQ_INT(40, evaluate_point(board, init_point(7, 9), WHITE));
    EXPECT_EQ_INT(40, evaluate_point(board, init_point(7, 6), BLACK));
    EXPECT_EQ_INT(31, evaluate_point(board, init_point(7, 6), WHITE));
    EXPECT_EQ_INT(130, evaluate_point(board, init_point(6, 6), BLACK));
    EXPECT_EQ_INT(31, evaluate_point(board, init_point(6, 6), WHITE));
    EXPECT_EQ_INT(130, evaluate_point(board, init_point(8, 6), BLACK));
    EXPECT_EQ_INT(31, evaluate_point(board, init_point(8, 6), WHITE));
    EXPECT_EQ_INT(121, evaluate_point(board, init_point(6, 7), BLACK));
    EXPECT_EQ_INT(121, evaluate_point(board, init_point(6, 7), WHITE));
    EXPECT_EQ_INT(121, evaluate_point(board, init_point(6, 8), BLACK));
    EXPECT_EQ_INT(121, evaluate_point(board, init_point(6, 8), WHITE));
    EXPECT_EQ_INT(31, evaluate_point(board, init_point(6, 9), BLACK));
    EXPECT_EQ_INT(130, evaluate_point(board, init_point(6, 9), WHITE));


    EXPECT_EQ_INT(40, evaluate_point(board, init_point(5, 6), BLACK));
    EXPECT_EQ_INT(80, evaluate_point(board, init_point(5, 6), WHITE));
}


static void testPut(Board *board) {
    put(board, init_point(7, 8), WHITE);
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    printf("%-3d", board->blackScore[i][j]);
	}
	printf("\n");
    }
    printf("\n\n");
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    printf("%-3d", board->whiteScore[i][j]);
	}
	printf("\n");
    }

    printf("\n\n");
}

static void testMwin(Board *board) {
    board->board[8][8] = WHITE;
    board->board[9][8] = WHITE;
    board->board[10][8] = WHITE;
    board->board[11][8] = WHITE;
    EXPECT_EQ_INT(WHITE, mwin(board));
}

void testGobang() {
    Board b;
    Board *board = &b;
    initBoard(board);
    board->board[7][7] = BLACK;
    draw(board);
    testPut(board);

    testHasNeighbors(board);

    testGen(board);
    testEvaluate_Point(board);

    testMwin(board);
}




int main() {
    testGobang(); 
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    exit(0);
}
