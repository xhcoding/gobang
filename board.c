#include "gobang.h"

void initBoard(int ***board, int ***blackScore, int ***whiteScore) {
    *board = (int **)malloc(SIZE * sizeof(sizeof(int *)));
    *blackScore = (int **)malloc(SIZE * sizeof(sizeof(int *)));
    *whiteScore = (int **)malloc(SIZE * sizeof(sizeof(int *)));
    for (int i = 0; i < SIZE; i++) {
	(*board)[i] = (int *)malloc(SIZE * sizeof(int));
	(*whiteScore)[i] = (int *)malloc(SIZE * sizeof(int));
	(*blackScore)[i] = (int *)malloc(SIZE * sizeof(int));
    }
    
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    (*board)[i][j] = EMPTY;
	    (*blackScore)[i][j] = 0;
	    (*whiteScore)[i][j] = 0;
	}
    }

}


void draw(int **board) {
    system("clear");
    printf("  ");
    for (int i = 0;i < SIZE; i++) {
	printf(" %1x", i);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
	for (int j = -1; j < SIZE; j++) {
	    if (j == -1) {
		printf(" %x", i);
	    }
	    else if (board[i][j] == 0) {
		printf(" *");
	    } else if (board[i][j] == 1) {
		printf(" X");
	    } else if (board[i][j] == 2){
		printf(" O");
	    }
	}
	printf("\n");
    }
    printf("\n");
}


int calc(int **board, int i, int j, int d1, int d2, int t) {
    int x = 0, y = 0;
    int s = 0;
    for (int k = -4;k <= 4; k++) {
	y = j - k * d1;
	x = i - k * d2;
	if (y < 0 || x > (SIZE - 1) || x < 0 || y > (SIZE - 1)) {
	    continue;
	}
	if (board[x][y] == t) {
	    s ++;
	    if (s == 5) {
		break;
	    }
	} else {
	    s = 0;
	}
    }
    return s;
}

int win(int **board, int x, int y, int t) {
    if (calc(board, x, y, 1, 0, t) >= 5 ||
	calc(board, x, y, 0, 1, t) >= 5 ||
	calc(board, x, y, 1, 1, t) >= 5 ||
	calc(board, x, y, -1, 1, t) >= 5) {
	return 1;
    }
    return 0;
}


int mwin(int **board) {
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    int tp = board[i][j];

	    if (tp != EMPTY) {
		int r = win(board, i, j, tp);
		if (r) {
		    return tp;
		}
	    }
	}
    }
    return 0;
}

void put(int **board, int x, int y, int t, int **blackScore, int **whiteScore) {
    board[x][y] = t;
    updateScoreRadius(board, x, y, blackScore, whiteScore);
}

void delete(int **board, int x, int y, int t, int **blackScore, int **whiteScore) {
    board[x][y] = EMPTY;
    updateScoreRadius(board, x, y, blackScore, whiteScore);
}

