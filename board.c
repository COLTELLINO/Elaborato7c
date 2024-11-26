#include "board.h"
#include <stdlib.h>

#define IS_MINE(board,i,j) (board[i][j] == UNKN_MINE || board[i][j] == FLAG_MINE || board[i][j] ==MINE)
#define IS_FLAG(board,i,j) (board[i][j] == FLAG_MINE || board[i][j] == FLAG_FREE)
#define IS_UNKNOW(board,i,j) (board[i][j] == UNKN_MINE || board[i][j] == UNKN_FREE)
#define SET_LIMIT int i0 = (i == 0) ? 0 : (i - 1); int j0 = (j == 0) ? 0 : (j - 1); int i1 = (i ==(rows - 1)) ? i : (i + 1); int j1 = (j == (cols - 1)) ? j : (j + 1);
#define ABS(x,y) ((x) > (y) ? (x)-(y) : (y)-(x))

static int count(int board[][GAME_COLS], unsigned int rows, unsigned int cols, int i, int j) {
	int a, b, c = 0;
	SET_LIMIT 
		for (a = i0; a <= i1; a++)
			for (b = j0; b <= j1; b++)
				if (a != i || b != j)
					c += IS_MINE(board, a, b);
	return c; 
}

static int count_flagged(int board[][GAME_COLS], unsigned int rows, unsigned int cols, int i, int j) {

	int a, b, c = 0;
	SET_LIMIT 
		for (a = i0; a <= i1; a++)
			for (b = j0; b <= j1; b++)
				if (a != i || b != j)
					c += IS_FLAG(board, a, b);
	return c; 
}

static int setup_unknown(int board[][GAME_COLS], unsigned int rows, unsigned int cols, int i, int j) {

	int s = 0;
	if (i >= 0 && i < rows && j >= 0 && j < cols && board[i][j] == UNKN_FREE) {
		int c = count(board, rows, cols, i, j); 
		switch (c) {
		case 0: board[i][j] = C0;
			s += setup_unknown(board, rows, cols, i - 1, j);
			s += setup_unknown(board, rows, cols, i, j - 1); 
			s += setup_unknown(board, rows, cols, i + 1, j); 
			s += setup_unknown(board, rows, cols, i, j + 1);
			s += setup_unknown(board, rows, cols, i + 1, j + 1);
			s += setup_unknown(board, rows, cols, i - 1, j + 1);
			s += setup_unknown(board, rows, cols, i - 1, j - 1);
			s += setup_unknown(board, rows, cols, i + 1, j - 1);
			break;
		case 1: board[i][j] = C1; break;
		case 2: board[i][j] = C2; break;
		case 3: board[i][j] = C3; break;
		case 4: board[i][j] = C4; break;
		case 5: board[i][j] = C5; break;
		case 6: board[i][j] = C6; break;
		case 7: board[i][j] = C7; break;
		case 8: board[i][j] = C8; break;
		}
		return s + 1;
	}
	return s;
}

void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines) {

	unsigned int a, b, c = 0;
	srand(time(NULL));

	for (a = 0; a < rows; a++) {
		for (b = 0; b < cols; b++) {
			board[a][b] = UNKN_FREE;
		}
	}
	while (c != num_mines) {
		a = rand() % rows;
		b = rand() % cols;
		if (board[a][b] == UNKN_FREE && (ABS(a, i) > 1 || ABS(b, i) > 1)) {
			board[a][b] = UNKN_MINE;
			c++;
		}
	}
}

int flag_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

	int c = 0;
	switch (board[i][j]) {
	case UNKN_FREE:
		board[i][j] = FLAG_FREE; c = 1; break;
	case UNKN_MINE:
		board[i][j] = FLAG_MINE; c = 1; break;
	case FLAG_MINE:
		board[i][j] = UNKN_MINE; c = -1; break;
	case FLAG_FREE:
		board[i][j] = UNKN_FREE; c = -1; break;
	default: c = 0; break;
	}
	return c;
}

int display_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

	if (board[i][j] == UNKN_MINE)
	{
		board[i][j] = MINE;
		return -1;
	}
	else if (board[i][j] == UNKN_FREE)
	{
		return setup_unknown(board, rows, cols, i, j);
	}
	return 0;
}

int expand_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j)
{
	int a, b, ndis, tndis = 0;
	SET_LIMIT

		if (board[i][j] > C0 && board[i][j] < C8) {
			if (count_flagged(board, rows, cols, i, j) == board[i][j]) {
				for (a = i0; a <= i1; a++) {
					for (b = j0; b <= j1; b++) {
						if (a != i || b != j) {
							if (IS_UNKNOW(board, a, b)) {
								ndis = display_board(board, rows, cols, a, b);
								if (ndis == -1)
									return -1;
								else tndis += ndis;
							}
						}
					}
				}
				return tndis;
			}
		}
	return 0;
}