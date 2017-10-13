#include "gobang.h"

void initBoard(Board *board) {
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    board->board[i][j] = EMPTY;
	    board->whiteScore[i][j] = 0;
	    board->blackScore[i][j] = 0;
	}
    }

}


void draw(Board *board) {
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
	    else if (board->board[i][j] == 0) {
		printf(" *");
	    } else if (board->board[i][j] == 1) {
		printf(" X");
	    } else if (board->board[i][j] == 2){
		printf(" O");
	    }
	}
	printf("\n");
    }
    printf("\n");
}


int calc(Board *board, Point p, int d1, int d2, int role) {
    int x = 0, y = 0;
    int s = 0;
    for (int k = -4;k <= 4; k++) {
	y = p.y - k * d1;
	x = p.x - k * d2;
	if (y < 0 || x > (SIZE - 1) || x < 0 || y > (SIZE - 1)) {
	    continue;
	}
	if (board->board[x][y] == role) {
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

int win(Board *board, Point p, int role) {
    if (calc(board, p, 1, 0, role) >= 5 ||
	calc(board, p, 0, 1, role) >= 5 ||
	calc(board, p, 1, 1, role) >= 5 ||
	calc(board, p, -1, 1, role) >= 5) {
	return 1;
    }
    return 0;
}


int mwin(Board *board) {
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    int role = board->board[i][j];
	    if (role != EMPTY) {
		int r = win(board, init_point(i, j), role);
		if (r) {
		    return role;
		}

	    }
	}
    }
    return 0;
}

void put(Board *board, Point p, int role) {
    board->board[p.x][p.y] = role;
    updateScoreRadius(board, p);
}

void getoff(Board *board, Point p, int role) {
    board->board[p.x][p.y] = EMPTY;
    updateScoreRadius(board, p);
}

