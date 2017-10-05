#include "gobang.h"

static int p = 0;

int hasNeighbors(int **board, int x, int y, int distance, int count) {
    int startX = x - distance;
    int endX = x + distance;
    int startY = y - distance;
    int endY = y + distance;

    for (int i = startX; i <= endX; i++) {
	if (i < 0 || i > SIZE - 1) {
	    continue;
	}
	for (int j = startY; j <= endY; j++) {
	    if (j < 0 || j > SIZE - 1) {
		continue;
	    }
	    if (i == x && j == y)  {
		continue;
	    }
	    if (board[i][j] != EMPTY) {
		count--;
		if (count <= 0) {
		    return 1;
		}
	    }
	}
    }
    return 0;
}


int gen(int **board, int deep, int *points) {
    int c1 = 0, c2 = 0;
    int neighbor[SIZE * SIZE * 2];
    int nextNeighbor[SIZE * SIZE * 2];
    for (int i = 0;i < SIZE; i++) {
	for (int j = 0;j < SIZE; j++) {
	    if (board[i][j] == EMPTY) {
		if (hasNeighbors(board, i, j, 1, 1)) {
		    c1++;
		    neighbor[c1 * 2 - 2] = i;
		    neighbor[c1 * 2 - 1] = j;
		} else if (deep >= 2 && hasNeighbors(board, i, j, 2, 2)) {
		    c2++;
		    nextNeighbor[c2 * 2 - 2] = i;
		    nextNeighbor[c2 * 2 - 1] = j;
		}
	    }
	} 
    }
    memcpy(points, neighbor, sizeof(int) * c1 * 2);
    memcpy(points + c1 * 2, nextNeighbor, sizeof(int) * c2 * 2);
    return c1 + c2;
}

int maxmin(int **board, int deep, int *x, int *y, int **blackScore, int **whiteScore) {
    int best = MIN;
    int points[SIZE * SIZE * 2];
    int count = gen(board, deep, points);

    for (int i = 0; i < count; i++) {
	//board[points[i * 2]][points[i * 2 + ]] = BLACK;// 尝试一个棋子
	put(board, points[i * 2], points[i * 2 + 1], BLACK, blackScore, whiteScore);
	int v = min(board, deep - 1, x, y, WHITE, blackScore, whiteScore); // 找到下一层的最小值
	if (v >= best) {
	    best = v;
	    *x = points[i * 2];
	    *y = points[i * 2 + 1];
	}

	delete(board, points[i * 2], points[i * 2 + 1], EMPTY, blackScore, whiteScore);
    }
    return best;
}


int min(int **board, int deep, int *x, int *y, int t, int **blackScore, int **whiteScore) {
    int v = evaluate(board, t, blackScore, whiteScore);
    //printf("min p = %d deep = %d v = %d\n", p, deep, v);
    p++;
    if (deep <= 0 || mwin(board)) {
	return v;
    }
    int best = MAX;
    int points[SIZE * SIZE * 2];
    int count = gen(board, deep, points);
    
    for (int i = 0; i < count; i++) {
	//board[points[i * 2]][points[i * 2 + 1]] = WHITE;// 尝试一个棋子
	put(board, points[i * 2], points[i * 2 + 1], WHITE, blackScore, whiteScore);
	int v = max(board, deep - 1, x, y, BLACK, blackScore, whiteScore);
	delete(board, points[i * 2], points[i * 2 + 1], EMPTY, blackScore, whiteScore);
	if (v < best) {
	    best = v;
	    *x = points[i * 2];
	    *y = points[i * 2 + 1];

	}
    }
#ifdef PRINT_BEST
    printf("min best = %d\n", best);
#endif
    return best;
}



int max(int **board, int deep, int *x, int *y, int t, int **blackScore, int **whiteScore) {
    int v = evaluate(board, t, blackScore, whiteScore);
    //printf("max p = %d deep = %d v = %d\n", p, deep, v);
    p++;
    if (deep <= 0 || mwin(board)) {
	return v;
    }
    int best = MIN;
    int points[SIZE * SIZE * 2];
    int count = gen(board, deep, points);
    
    for (int i = 0; i < count; i++) {
	//	board[points[i * 2]][points[i * 2 + 1]] = BLACK;// 尝试一个棋子 /* FIXME:  */

	put(board, points[i * 2], points[i * 2 + 1], BLACK, blackScore, whiteScore);
	int v = min(board, deep - 1, x, y, WHITE, blackScore, whiteScore);
	delete(board, points[i * 2], points[i * 2 + 1], EMPTY, blackScore, whiteScore);
	if (v > best) {
	    best = v;
	    *x = points[i * 2];
	    *y = points[i * 2 + 1];

	}
    }
#ifdef PRINT_BEST
    printf("max best = %d\n", best);
#endif
    return best;
}


