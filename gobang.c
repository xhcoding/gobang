#include "gobang.h"
/* TODO:  board whiteScore blackScore*/


// 搜索深度

int deep = 4;
/**
 * AI下子
 */
void blackPut(int **board, int **blackScore, int **whiteScore);

int blackScore[SIZE][SIZE]; // 黑棋的分值
int whiteScore[SIZE][SIZE]; // 白棋的分值

void input(int **board, int *x, int *y, int t);

int main() {

    /* TODO:  free board*/
    int **board, **blackScore, **whiteScore;

    initBoard(&board, &blackScore, &whiteScore);
    board[7][7] = BLACK;
    draw(board);
    int x, y;
    int t = 1;
    int s = 0;
    for(;;) {
	input(board, &x, &y, WHITE);
	put(board, x, y, WHITE, blackScore, whiteScore);
	if (win(board, x, y, WHITE)) {
	    printf("白棋胜利!\n");
	    exit(0);
	}
	draw(board);
	blackPut(board, blackScore, whiteScore);
	draw(board);
	
    }
    return 0;
}


void input(int **board, int *x, int *y, int t) {
    for (;;) {
	if (t == 1) {
	    printf("请输入黑棋的位置：\n");
	} else if (t == 2) {
	    printf("请输入白棋的位置：\n");
	}
	while(scanf("%d %d", x, y) == 0) {
	    printf("请输入两个数字\n");
	    while(getchar() != '\n');
	}
	if (*x < 0 || *x > (SIZE - 1) || *y < 0 || *y > (SIZE - 1) || board[*x][*y] != 0) {
	    printf("无效的位置，请重新输入\n");
	} else {
	    break;
	}
    }
}




void blackPut(int **board, int **blackScore, int **whiteScore) {
    int x = 0, y = 0;
    int best = maxmin(board, deep, &x, &y, blackScore, whiteScore);
    put(board, x, y, BLACK, blackScore, whiteScore);
    if (win(board, x, y, BLACK)) {
	printf("黑棋胜利！\n");
	exit(0);
    }
}
