#include "gobang.h"


int evaluate(Board *board, int role) {
    int blackMaxScore = - FIVE;
    int whiteMaxScore = - FIVE;

    // 遍历出最高分
    for (int i = 0; i < SIZE; i++) {
    	for (int j = 0; j < SIZE; j ++) {
    	    if (board->board[i][j] == EMPTY) {
    		blackMaxScore = board->blackScore[i][j] > blackMaxScore ?
    		    board->blackScore[i][j] : blackMaxScore;
    		whiteMaxScore = board->whiteScore[i][j] > whiteMaxScore ?
    		    board->whiteScore[i][j] : whiteMaxScore;
    	    }
    	}
    }
    
    int result = (role == BLACK ? 1 : -1) * (blackMaxScore - whiteMaxScore);
    return result;
}

int evaluate_point(Board *board, Point p, int role) {
    int x = p.x;
    int y = p.y;

    int result = 0;
    int count = 0, block = 0;
    int secondCount = 0; // 另一方向的count
    
    int empty = -1;
    count = 1;

    
    // 横向计算
    // 向右
    for (int i = y + 1; true; i++) {
	if (i >= SIZE) {
	    block++;
	    break;
	}
	int tp = board->board[x][i];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		i + 1 < SIZE - 1 &&
		board->board[x][i + 1] == role) { // DONE: i + 1 >= SIZE ?
		empty = count;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    count++;
	    continue;
	} else {
	    block++;
	    break;
	}
    }
    
    // 向左
    for (int i = y - 1; true; i--) {
	if (i < 0) {
	    block++;
	    break;
	}
	int tp = board->board[x][i];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		i - 1 > 0 &&
		board->board[x][i - 1] == role) { // DONE: i - 1 < 0 ?
		empty = 0;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    secondCount++;
	    if (empty != -1) {
		empty++;
	    }
	    continue;
	} else {
	    block++;
	    break;
	}
    }

    count += secondCount;
    result += type2score(count, block, empty);

    // reset
    count = 1;
    block = 0;
    empty = -1;
    secondCount = 0;
    // |
    for (int i = x + 1; true; i++) {
	if (i >= SIZE) {
	    block++;
	    break;
	}
	int tp = board->board[i][y];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		i + 1 < SIZE - 1 &&
		board->board[i+1][y] == role) {
		empty = count;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    count++;
	    continue;
	} else {
	    block++;
	    break;
	}
    }

    for (int i = x - 1; true; i--) {
	if (i < 0) {
	    block++;
	    break;
	}
	int tp = board->board[i][y];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		i - 1 > 0 &&
		board->board[i - 1][y] == role) {
		empty = 0;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    secondCount++;
	    if (empty != -1) {
		empty++;
	    }
	    continue;
	} else {
	    block++;
	    break;
	}
	
    }
    count += secondCount;
    result += type2score(count, block, empty);

    // reset
    count = 1;
    block = 0;
    empty = -1;
    secondCount = 0;

    //"\"
    for (int i = 1; true;i++) {
	int x0 = i + x;
	int y0 = i + y;
	if (x0 >= SIZE || y0 >= SIZE) {
	    block++;
	    break;
	}
	int tp = board->board[x0][y0];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		(x0 + 1 < SIZE - 1 && y0 + 1 < SIZE - 1) &&
		board->board[x0 + 1][y0 + 1] == role) {
		empty = count;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    count++;
	    continue;
	} else {
	    block++;
	    break;
	}
    }

    for (int i = 1; true; i++) {
	int x0 = x - i;
	int y0 = y - i;
	if (x0 < 0 || y0 < 0) {
	    block++;
	    break;
	}
	int tp = board->board[x0][y0];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		(x0 - 1 > 0 && y0 - 1 > 0) &&
		board->board[x0 - 1][y0 - 1] == role) {
		empty = 0;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    secondCount++;
	    if (empty != -1) {
		empty++;
	    }
	    continue;
	} else {
	    block++;
	    break;
	}
	
    }
    count += secondCount;
    result += type2score(count, block, empty);

    // reset
    count = 1;
    block = 0;
    empty = -1;
    secondCount = 0;

    //"/"
    for (int i = 1; true;i++) {
	int x0 = x + i;
	int y0 = y - i;
	if (x0 >= SIZE || y0 < 0) {
	    block++;
	    break;
	}
	int tp = board->board[x0][y0];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		(x0 + 1 < SIZE - 1 && y0 - 1 > 0) &&
		board->board[x0 + 1][y0 - 1] == role) {
		empty = count;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    count++;
	    continue;
	} else {
	    block++;
	    break;
	}
    }
    

    for (int i = 1; true; i++) {
	int x0 = x - i;
	int y0 = y + i;
	if (x0 < 0 || y0 >= SIZE) {
	    block++;
	    break;
	}
	int tp = board->board[x0][y0];
	if (tp == EMPTY) {
	    if (empty == -1 &&
		(x0 - 1 > 0 && y0 + 1 < SIZE - 1) &&
		board->board[x0 - 1][y0 + 1] == role) {
		empty = 0;
		continue;
	    } else {
		break;
	    }
	}
	if (tp == role) {
	    secondCount++;
	    if (empty != -1) {
		empty++;
	    }
	    continue;
	} else {
	    block++;
	    break;
	}
	
    }
    count += secondCount;
    result += type2score(count, block, empty);

    // 修复冲4
    if (result < FOUR && result >= BLOCKED_FOUR) {
	if (result >= BLOCKED_FOUR && result < (BLOCKED_FOUR + THREE)) {
	    // 单独冲四，意义不大
	    result =  THREE;
	} else if (result >= BLOCKED_FOUR + THREE &&
		   result  < BLOCKED_FOUR  * 2) {
	    result =  FOUR; // 冲四活三
	} else {
	    // 双冲四
	    result = FOUR * 2;
	}
    }
    
    return result;
}

int type2score(int count, int block, int empty) {
    
    // 没有空位
    if (empty <= 0) {
	if (count >= 5) {
	    return FIVE;
	}
	if (block == 0) {
	    switch(count) {
	    case 1: return ONE;
	    case 2: return TWO;
	    case 3: return THREE;
	    case 4: return FOUR;
	    }
	}
	if (block == 1) {
	    switch(count) {
	    case 1: return BLOCKED_ONE;
	    case 2: return BLOCKED_TWO;
	    case 3: return BLOCKED_THREE;
	    case 4: return BLOCKED_FOUR;
	    }

	}
    } else if(empty == 1 || empty == count - 1) {
	// 第一个是空位
	if (count >= 6) {
	    return FIVE;
	}
	if (block == 0) {
	    switch(count) {
	    case 2: return TWO / 2;
	    case 3: return THREE;
	    case 4: return BLOCKED_FOUR;
	    case 5: return FOUR;
	    }
	}
	if (block == 1) {
	    switch(count) {
	    case 2: return BLOCKED_TWO;
	    case 3: return BLOCKED_THREE;
	    case 4: return BLOCKED_FOUR;
	    case 5: return BLOCKED_FOUR;

	    }
	}
	
    } else if (empty == 2 || empty == count - 2) {
	// 第二个是空位
	if (count >= 7) {
	    return FIVE;
	}
	if (block == 0) {
	    switch(count) {
	    case 3: return THREE;
	    case 4:
	    case 5: return BLOCKED_FOUR;
	    case 6: return FOUR;
	    }
	}
	if (block == 1) {
	    switch(count) {
	    case 3: return BLOCKED_THREE;
	    case 4: return BLOCKED_FOUR;
	    case 5: return BLOCKED_FOUR;
	    case 6: return FOUR;
	    }
	}
	if (block == 2) {
	    switch(count) {
	    case 4:
	    case 5:
	    case 6: return BLOCKED_FOUR;
	    }
	}
	
    } else if (empty == 3 || empty == count - 3) {
	if (count >= 8) {
	    return FIVE;
	}
	if (block == 0) {
	    switch(count) {
	    case 4:
	    case 5: return THREE;
	    case 6: return BLOCKED_FOUR;
	    case 7: return FOUR;
	    }
	}
	if (block == 1) {
	    switch(count) {
	    case 4:
	    case 5:
	    case 6: return BLOCKED_FOUR;
	    case 7: return FOUR;
	    }
	}
	if (block == 2) {
	    switch(count) {
	    case 4:
	    case 5:
	    case 6:
	    case 7: return BLOCKED_FOUR;
	    }
	}
    } else if (empty == 4 || empty == count - 4) {
	if (count >= 9) {
	    return FIVE;
	}
	if (block == 0) {
	    switch(count) {
	    case 5:
	    case 6:
	    case 7:
	    case 8: return FOUR;
	    }
	}
	if (block == 1) {
	    switch (count) {
	    case 4:
	    case 5:
	    case 6:
	    case 7: return BLOCKED_FOUR;
	    case 8: return FOUR;
	    }
	}
	if (block == 2) {
	    switch(count) {
	    case 5:
	    case 6:
	    case 7:
	    case 8: return BLOCKED_FOUR;
	    }
	}
    } else if (empty == 5 || empty == count - 5) {
	return FIVE;
    }

    
    return 0;
}


void updateScore(Board *board, Point p) {
    int black = evaluate_point(board, p, BLACK);
    int white = evaluate_point(board, p, WHITE);
    board->blackScore[p.x][p.y] = white;
    board->whiteScore[p.x][p.y] = black;
}



void updateScoreRadius(Board *board, Point p) {
    int x = p.x;
    int y = p.y;
    int radius = 8;
    // -
    for (int i = -radius; i < radius; i++) {
	int x0 = x, y0 = y + i;
	if (y0 < 0) {
	    continue;
	}
	if (y0 >= SIZE) {
	    break;
	}
	if (board->board[x0][y0] != EMPTY) {
	    continue;
	}
	updateScore(board, init_point(x0, y0));
    }
    //|
    for (int i = -radius; i < radius; i++) {
	int x0 = x + i, y0 = y;
	if (x0 < 0) {
	    continue;
	}
	if (x0 >= SIZE) {
	    break;
	}
	if (board->board[x0][y0] != EMPTY) {
	    continue;
	}
	updateScore(board, init_point(x0, y0));
    }
    //"\"
    for (int i = -radius; i < radius; i++) {
	int x0 = x + i, y0 = y + i;
	if (y0 < 0 || x0 <0) {
	    continue;
	}
	if (y0 >= SIZE || x0 >= SIZE) {
	    break;
	}
	if (board->board[x0][y0] != EMPTY) {
	    continue;
	}
	updateScore(board, init_point(x0, y0));
    }
    // "/"
    for (int i = -radius; i < radius; i++) {
	int x0 = x + i, y0 = y - i;
	if (y0 < 0 || x0 < 0) {
	    continue;
	}
	if (y0 >= SIZE || x0 >= SIZE) {
	    break;
	}
	if (board->board[x0][y0] != EMPTY) {
	    continue;
	}
	updateScore(board, init_point(x0, y0));
    }
    
}


