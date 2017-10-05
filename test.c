#include "gobang.h"


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



static void testHasNeighbors(int **board) {
    // distance = 1, count = 1
    EXPECT_EQ_INT(1, hasNeighbors(board, 7, 9, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 10, 1, 1)); 
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 11, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 7, 6, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 5, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 4, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 6, 6, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 6, 7, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 6, 8, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 6, 9, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 6, 5, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 6, 10, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 8, 6, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 8, 7, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 8, 8, 1, 1));
    EXPECT_EQ_INT(1, hasNeighbors(board, 8, 9, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 8, 5, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 8, 10, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 5, 7, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 5, 8, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 9, 7, 1, 1));
    EXPECT_EQ_INT(0, hasNeighbors(board, 9, 8, 1, 1));

    // distance = 2, count = 2
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 10, 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 11, 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 5, 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, 7, 4, 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, 6, 5, 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, 6, 10, 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, 8, 5, 2, 2));
    EXPECT_EQ_INT(0, hasNeighbors(board, 8, 10, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 5, 6, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 5, 7, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 5, 8, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 5, 9, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 9, 6, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 9, 7, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 9, 8, 2, 2));
    EXPECT_EQ_INT(1, hasNeighbors(board, 9, 9, 2, 2));
    
 
}

static void testPoints(int *points) {
    EXPECT_EQ_INT(6, points[0]);
    EXPECT_EQ_INT(6, points[1]);
    EXPECT_EQ_INT(6, points[2]);
    EXPECT_EQ_INT(7, points[3]);
    EXPECT_EQ_INT(6, points[4]);
    EXPECT_EQ_INT(8, points[5]);
    EXPECT_EQ_INT(6, points[6]);
    EXPECT_EQ_INT(9, points[7]);
    EXPECT_EQ_INT(7, points[8]);
    EXPECT_EQ_INT(6, points[9]);
    EXPECT_EQ_INT(7, points[10]);
    EXPECT_EQ_INT(9, points[11]);
    EXPECT_EQ_INT(8, points[12]);
    EXPECT_EQ_INT(6, points[13]);
    EXPECT_EQ_INT(8, points[14]);
    EXPECT_EQ_INT(7, points[15]);
    EXPECT_EQ_INT(8, points[16]);
    EXPECT_EQ_INT(8, points[17]);
    EXPECT_EQ_INT(8, points[18]);
    EXPECT_EQ_INT(9, points[19]);
    EXPECT_EQ_INT(5, points[20]);
    EXPECT_EQ_INT(6, points[21]);
    EXPECT_EQ_INT(5, points[22]);
    EXPECT_EQ_INT(7, points[23]);
    EXPECT_EQ_INT(5, points[24]);
    EXPECT_EQ_INT(8, points[25]);
    EXPECT_EQ_INT(5, points[26]);
    EXPECT_EQ_INT(9, points[27]);
    EXPECT_EQ_INT(9, points[28]);
    EXPECT_EQ_INT(6, points[29]);
    EXPECT_EQ_INT(9, points[30]);
    EXPECT_EQ_INT(7, points[31]);
    EXPECT_EQ_INT(9, points[32]);
    EXPECT_EQ_INT(8, points[33]);
    EXPECT_EQ_INT(9, points[34]);
    EXPECT_EQ_INT(9, points[35]);
    EXPECT_EQ_INT(-1, points[36]);
    EXPECT_EQ_INT(-1, points[37]);
    EXPECT_EQ_INT(-1, points[38]);
    EXPECT_EQ_INT(-1, points[39]);
    EXPECT_EQ_INT(-1, points[40]);
    
}

static void testGen(int **board) {

    int points[SIZE * SIZE * 2];
    memset(points, -1, SIZE * SIZE * 2);
    EXPECT_EQ_INT(18, gen(board, 6, points));
    testPoints(points);
}

static void testEvaluate_Point(int **board) {
    EXPECT_EQ_INT(31, evaluate_point(board, 7, 9, BLACK));
    EXPECT_EQ_INT(40, evaluate_point(board, 7, 9, WHITE));
    EXPECT_EQ_INT(40, evaluate_point(board, 7, 6, BLACK));
    EXPECT_EQ_INT(31, evaluate_point(board, 7, 6, WHITE));
    EXPECT_EQ_INT(130, evaluate_point(board, 6, 6, BLACK));
    EXPECT_EQ_INT(31, evaluate_point(board, 6, 6, WHITE));
    EXPECT_EQ_INT(130, evaluate_point(board, 8, 6, BLACK));
    EXPECT_EQ_INT(31, evaluate_point(board, 8, 6, WHITE));
    EXPECT_EQ_INT(121, evaluate_point(board, 6, 7, BLACK));
    EXPECT_EQ_INT(121, evaluate_point(board, 6, 7, WHITE));
    EXPECT_EQ_INT(121, evaluate_point(board, 6, 8, BLACK));
    EXPECT_EQ_INT(121, evaluate_point(board, 6, 8, WHITE));
    EXPECT_EQ_INT(31, evaluate_point(board, 6, 9, BLACK));
    EXPECT_EQ_INT(130, evaluate_point(board, 6, 9, WHITE));


    EXPECT_EQ_INT(40, evaluate_point(board, 5, 6, BLACK));
    EXPECT_EQ_INT(80, evaluate_point(board, 5, 6, WHITE));
}


static void testPut(int **board, int **blackScore, int **whiteScore) {
    put(board, 7, 8, WHITE, blackScore, whiteScore);
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    printf("%-3d", blackScore[i][j]);
	}
	printf("\n");
    }
    printf("\n\n");
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    printf("%-3d", whiteScore[i][j]);
	}
	printf("\n");
    }

    printf("\n\n");

}

void testGobang() {
    int **board, **blackScore, **whiteScore;
    initBoard(&board, &blackScore, &whiteScore);
    board[7][7] = BLACK;
    draw(board);
    testPut(board, blackScore, whiteScore);

    testHasNeighbors(board);

    testGen(board);
    testEvaluate_Point(board);
}




int main() {
    testGobang(); 
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    exit(0);
}
