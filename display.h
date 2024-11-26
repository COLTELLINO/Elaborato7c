#ifndef DISPLAY_H
#define DISPLAY_H

#include <curses.h>
#include "game.h"
#include "board.h"

#define UNKN_SYMBOL   '-'
#define UNKN_SYMBOL_B '+'
#define MINE_SYMBOL   '*'  
#define FLAG_SYMBOL   ACS_DIAMOND
#define CURS_SYMBOL_LEFT  '<'
#define CURS_SYMBOL_RIGHT '>'

#define QUIT_KEY    'q'
#define RESTART_KEY 'r'
#define FLAG_KEY    'f'
#define EXPAND_KEY  'e'
#define DISPLAY_KEY 'd'
#define LEFT_KEY     KEY_LEFT
#define RIGHT_KEY    KEY_RIGHT
#define DOWN_KEY     KEY_DOWN
#define UP_KEY       KEY_UP



/*
 * Opens the graphical display.
 */
void display_open(void);

/*
 * Closes the graphical display.
 */
void display_close(void);

/*
 * Plots the current board into the graphical display.
 */
void display_plot(struct game *G);

/*
 * Plots the final board into the graphical display.
 */
void display_gameover(struct game *G);

/* 
 * Read from keyboard.
 */
int display_read(void);



#endif
