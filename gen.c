#include "gobang.h"
#include "list/list.h"
static int p = 0;

int hasNeighbors(Board *board, Point p, int distance, int count) {
    int startX = p.x - distance;
    int endX = p.x + distance;
    int startY = p.y - distance;
    int endY = p.y + distance;

    for (int i = startX; i <= endX; i++) {
	if (i < 0 || i > SIZE - 1) {
	    continue;
	}
	for (int j = startY; j <= endY; j++) {
	    if (j < 0 || j > SIZE - 1) {
		continue;
	    }
	    if (i == p.x && j == p.y)  {
		continue;
	    }
	    if (board->board[i][j] != EMPTY) {
		count--;
		if (count <= 0) {
		    return 1;
		}
	    }
	}
    }
    return 0;
}


Points *gen(Board *board, int deep) {

    Points *fives = get_empty_list();

    Points *fours = get_empty_list();

    Points *twothrees = get_empty_list();

    Points *threes = get_empty_list();

    Points *twos = get_empty_list();

    Points *neighbor = get_empty_list();

    Points *nextNeighbor = get_empty_list();
    
    for (int i = 0;i < SIZE; i++) {
	for (int j = 0;j < SIZE; j++) {
	    Point p = init_point(i, j);
	    if (board->board[i][j] == EMPTY) {
		if (hasNeighbors(board, p, 1, 1)) {
		    int scoreBlack = evaluate_point(board, p, BLACK);
		    int scoreWhite = evaluate_point(board, p, WHITE);

		    if (scoreBlack >= FIVE) {
			// 电脑成5
			Points *t = get_empty_list();
			push_back_list(t, p);
			return t;
		    } else if (scoreWhite >= FIVE) {
			// 玩家能不能连成5，遍历还没完成，说不定电脑能成5
			push_back_list(fives, p);
		    } else if (scoreBlack >= FOUR) {
			push_front_list(fours, p);
		    } else if (scoreWhite >= FOUR) {
			push_back_list(fours, p);
		    } else if (scoreBlack >= 2 * THREE) {
			push_front_list(twothrees, p);
		    } else if (scoreWhite >= 2 * THREE) {
			push_back_list(twothrees, p);
		    } else if (scoreBlack >= THREE) {
			push_front_list(threes, p);
		    } else if (scoreWhite >= THREE) {
			push_back_list(threes, p);
		    } else if (scoreBlack >= TWO) {
			push_front_list(twos, p);
		    } else if (scoreWhite >= TWO) {
			push_back_list(twos, p);
		    } else {	    
			push_back_list(neighbor, p);
		    }
		} else if (deep >= 2 && hasNeighbors(board, p, 2, 2)) {
		    push_back_list(nextNeighbor, p);
		}
	    }
	}
    }

    // 如果成5，直接返回
    if (fives->length != 0) {
	destroy_list(fours);
	destroy_list(twothrees);
	destroy_list(threes);
	destroy_list(twos);
	destroy_list(neighbor);
	destroy_list(nextNeighbor);
	return fives;
    }
    // 四
    if (fours->length != 0) {
	destroy_list(fives);
	destroy_list(twothrees);
	destroy_list(threes);
	destroy_list(twos);
	destroy_list(neighbor);
	destroy_list(nextNeighbor);

	return fours;
    }

    // 双三
    if (twothrees->length != 0) {
	destroy_list(fives);
	destroy_list(fours);
	destroy_list(threes);
	destroy_list(twos);
	destroy_list(neighbor);
	destroy_list(nextNeighbor);
	return twothrees;
    }

    append_back_list(threes, twos);
    append_back_list(threes, neighbor);
    append_back_list(threes, nextNeighbor);

    destroy_list(fives);
    destroy_list(fours);
    destroy_list(twothrees);
    destroy_list(twos);
    destroy_list(neighbor);
    destroy_list(nextNeighbor);

    return threes;
}

int maxmin(Board *board, int deep, Point *pp) {
    int best = MIN;
    List *points = gen(board, deep);

    for (int i = 0; i < points->length; i++) {
	Point tp = find_index_list(points, i);
	put(board, tp, BLACK);//MAX，选取一个方案
	int v = min(board, deep - 1, BLACK, MAX,  -MAX); // 找出min层的最小值
	if (v > best) {
	    best = v;
	    pp->x = tp.x;
	    pp->y = tp.y;
	}

	getoff(board, tp, EMPTY);
    }
    destroy_list(points);
    return best;
}


int min(Board *board, int deep, int role, int alpha, int beta) {
    int v = evaluate(board, role);
    if (deep <= 0 || mwin(board)) {
	return v;
    }
    int best = MAX;
    List *points = gen(board, deep);

    for (int i = 0; i < points->length; i++) {
	Point tp = find_index_list(points, i);
	put(board, tp, WHITE);
	int v = max(board, deep - 1, WHITE, best < alpha ? best : alpha, beta); // 找出max层的最大值
	getoff(board, tp, EMPTY);
	if (v < best) {
	    best = v;

	}
	if (v < beta) {
	    // beta剪枝
	    break;
	}
    }
#ifdef PRINT_BEST
    printf("min best = %d\n", best);
#endif
    destroy_list(points);
    return best;
}



int max(Board *board, int deep, int role, int alpha, int beta) {
    int v = evaluate(board, role);
    p++;
    if (deep <= 0 || mwin(board)) {
	return v;
    }
    int best = MIN;
    List *points = gen(board, deep);

    for (int i = 0; i < points->length; i++) {
	Point tp = find_index_list(points, i);
	put(board, tp, BLACK);
	int v = min(board, deep - 1, BLACK, alpha, best > beta ? best : beta);
	getoff(board, tp, EMPTY);
	if (v > best) {
	    best = v;
	}
	if (v > alpha) {
	    // alpha剪枝
	    break;
	}
    }
#ifdef PRINT_BEST
    printf("max best = %d\n", best);
#endif
    destroy_list(points);
    return best;
}


