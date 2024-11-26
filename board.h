#ifndef BOARD_H
#define BOARD_H

#include "game.h" // We need to know GAME_COLS

enum field {
	C0,         // The cell is sorrounded by 0 mines
	C1,         // The cell is sorrounded by 1 mine
	C2,         // The cell is sorrounded by 2 mines
	C3,         // The cell is sorrounded by 3 mines
	C4,         // The cell is sorrounded by 4 mines
	C5,         // The cell is sorrounded by 5 mines
	C6,         // The cell is sorrounded by 6 mines
	C7,         // The cell is sorrounded by 7 mines
	C8,         // The cell is sorrounded by 8 mines
	UNKN_FREE,  // The cell is not displayed and it is not a mine
	UNKN_MINE,  // The cell is not displayed and it is a mine
	FLAG_FREE,  // The cell is flagged and it is not a mine
	FLAG_MINE,  // The cell is flagged and it s a mine
	MINE        // The cell is a mine
};

/*
 * Fills the rows*cols board with num_mines random mines
 * leaving free the neighborhood of position i,j
 */
void random_board(int board[][GAME_COLS], unsigned int rows,
        unsigned int cols, unsigned int i, unsigned int j,
        unsigned int num_mines);

/*
 * Flags/unflags the i,j position in the board. Returns
 * - -1 if the position was flagged. Removes the flag
 * -  0 if the position is already displyed
 * -  1 if the position is not flagged and not already
 *    displayed. Puts a flag in position i,j. 
 */
int flag_board(int board[][GAME_COLS], unsigned int rows,
        unsigned int cols, unsigned int i, unsigned int j);

/*
 * Displays position i,j in the board. Returns the number of 
 * displayed cells or -1 if i,j contains a mine.
 */
int display_board(int board[][GAME_COLS], unsigned int rows,
        unsigned int cols, unsigned int i, unsigned int j);

/*
 * Expands all the free cells sourrounding  position i,j in
 * the board. Returns the number of expanded cells or -1 if
 * one contains a mine.
 */
int expand_board(int board[][GAME_COLS], unsigned int rows,
        unsigned int cols, unsigned int i, unsigned int j);

#endif
