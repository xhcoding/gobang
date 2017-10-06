#ifndef __gobang_h
#define __gobang_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define SIZE 15

/**
 * 空为0，黑棋为1，白棋为2
 */
typedef enum role {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
}ROLE;

/**
 * 棋型表示，从高到低一次为
 * 连五，活四，眠四，活三，活二/眠三，活一/眠二，眠一
 */
typedef enum chess_type {
    ONE = 10,
    TWO = 100,
    THREE = 1000,
    FOUR = 100000,
    FIVE = 100000,
    BLOCKED_ONE = 1,
    BLOCKED_TWO = 10,
    BLOCKED_THREE = 100,
    BLOCKED_FOUR = 10000
}CHESS_TYPE;


#define MAX FIVE * 10
#define MIN -MAX



/** 
 * 初始化棋盘
 */
void initBoard(int ***board, int ***whiteScore, int ***blackScore);

/**
 * 每一步生成所有可以落子的点
 * 点的坐标保存在points中
 * 返回：点的个数
 */
int gen(int **board, int deep, int *points);

/**
 * 极大极小搜索
 */
int maxmin(int **board, int deep, int *x, int *y, int **blackScore, int **whiteScore);
int min(int **board, int deep, int t, int alpha, int beta, int **blackScore, int **whiteScore);
int max(int **board, int deep, int t, int lapha, int beta, int **blackScore, int **whiteScore);



/**
 * 是否有邻居
 */
int hasNeighbors(int **board, int x, int y, int distance, int count);




// score.c

/**
 * 对当前棋面进行估分
 */
int evaluate(int **board, int t, int **blackScore, int **whiteScore);

/**
 * 在(x, y)这个空位下一个t类型的棋子后的打分函数
 */
int evaluate_point(int **board, int x, int y, int t);

/**
 * 根据连子个数，空位个数，以及阻挡个数判断类型，返回分数
 */
int type2score(int count, int block, int empty);

/**
 * 更新一个点的分值
 */
void updateScore(int **board, int x, int y, int **blackScore, int **whiteScore);

/**
 * 更新一个点附近的分值
 */
void updateScoreRadius(int **board, int x, int y, int **blackScore, int **whiteScore);




// board.c

int calc(int **board, int i, int y, int d1, int d2, int t);
int mwin(int **board);
int win(int **board, int x, int y, int t);
/**
 * 下一颗棋子
 */
void put(int **board, int x, int y, int t, int **blackScore, int **whiteScore);

/**
 * 移除一颗棋子
 */

void delete(int **board, int x, int y, int t, int **blackScore, int **whiteScore);



/**
 * 绘制棋盘
 */
void draw(int **board);

#endif
