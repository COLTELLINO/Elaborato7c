#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"


struct game *game_create(void) {
	struct game *G = NULL;
	int i,j;

	if((G = (struct game *)calloc(1,sizeof(struct game))) != NULL) {
		G->rows       = GAME_ROWS;
		G->cols       = GAME_COLS;
		G->mines      = (PERC_MINE * GAME_ROWS * GAME_COLS)/100;
		G->flags      = 0;
		G->displayed  = 0;
		// Puts the cursor approximatively in the middle of the board
		G->cursor_row = G->rows/2;
		G->cursor_col = G->cols/2;
	}
	for(i = 0; i < G->rows; i++)
		for(j = 0; j < G->cols; j++)
			G->board[i][j] = UNKN_FREE;

	return G;
}

void game_init(struct game *G) {
	random_board(G->board,G->rows,G->cols,G->cursor_row,G->cursor_col,G->mines);
}
 
void game_destroy(struct game *G) {
	free(G);
}

enum status game_update(struct game *G, enum input input) {
	enum status stat = CONTINUE;
	int c;

	switch(input) {
		case LEFT   : if(G->cursor_col > 0)         G->cursor_col--; break;
		case RIGHT  : if(G->cursor_col < G->cols-1) G->cursor_col++; break;
		case UP     : if(G->cursor_row > 0)         G->cursor_row--; break;
		case DOWN   : if(G->cursor_row < G->rows-1) G->cursor_row++; break;
		case FLAG   : G->flags += flag_board(G->board,G->rows,G->cols,G->cursor_row,G->cursor_col);
									if(G->flags > G->mines) // Undo flag
										G->flags += flag_board(G->board,G->rows,G->cols,G->cursor_row,G->cursor_col);
									break;
		case EXPAND : c = expand_board(G->board, G->rows, G->cols, G->cursor_row, G->cursor_col);
									// gameover if either an unflagged  mine or all the free cells have been  displayed
									if (c == -1 || (G->displayed += c) == G->rows*G->cols - G->mines)
										stat = GAMEOVER;
									break;
		case DISPLAY: c = display_board(G->board,G->rows,G->cols,G->cursor_row,G->cursor_col);
									// gameover if either a mine or all the free cells have been  displayed
									if(c == -1 || (G->displayed += c) == G->rows*G->cols - G->mines) 
										stat = GAMEOVER;
									break;
		default     :;
	}
	return stat;
}
