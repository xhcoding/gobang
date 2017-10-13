#include "gobang.h"
/* TODO:  board whiteScore blackScore*/


// 搜索深度

int deep = 6;
/**
 * AI下子
 */
void blackPut(Board *board);


void input(Board *board, Point *point, int role);

int main() {

    /* TODO:  free board*/
    Board b;
    Board *board = &b;
    initBoard(board);
    board->board[7][7] = BLACK;
    draw(board);
    int role = BLACK;
    int s = 0;
    Point p;
    for(;;) {
	input(board, &p, WHITE);
	put(board, p, WHITE);
	if (win(board, p, WHITE)) {
	    printf("白棋胜利!\n");
	    exit(0);
	}
	draw(board);
	blackPut(board);
	draw(board);

    }
    return 0;
}


void input(Board *board, Point *point, int role) {
    for (;;) {
	if (role == BLACK) {
	    printf("请输入黑棋的位置：\n");
	} else if (role == WHITE) {
	    printf("请输入白棋的位置：\n");
	}
	while(scanf("%d %d", &point->x, &point->y) == 0) {
	    printf("请输入两个数字\n");
	    while(getchar() != '\n');
	}
	if (point->x < 0 || point->x > (SIZE - 1) || point->y < 0 || point->y > (SIZE - 1) || board->board[point->x][point->y] != 0) {
	    printf("无效的位置，请重新输入\n");
	} else {
	    break;
	}
    }
}




void blackPut(Board *board) {
    Point p;
    int best = maxmin(board, deep, &p);
    put(board, p, BLACK);
    if (win(board, p, BLACK)) {
	printf("黑棋胜利！\n");
	exit(0);
    }
}
