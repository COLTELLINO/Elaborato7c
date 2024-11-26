#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "display.h"

// Draws the border of the board.
static void display_border(struct game *G, unsigned int start_row, unsigned int start_col);

// Draws the world.
static void display_world(struct game *G, unsigned int start_row, unsigned int start_col, int gameover);

void display_open(void) {
	initscr();
	cbreak();
	noecho();               
	keypad(stdscr, TRUE); // make keys work
	curs_set(0);          // hide cursor
	timeout(-1);          // Sets the waiting time for getch()
	if(has_colors()) {
		start_color();
		init_pair(1,COLOR_WHITE,COLOR_BLACK);
		init_pair(2,COLOR_BLUE,COLOR_BLACK);
		init_pair(3,COLOR_CYAN,COLOR_BLACK);
		init_pair(4,COLOR_GREEN,COLOR_BLACK);
		init_pair(5,COLOR_YELLOW,COLOR_BLACK);
		init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
		init_pair(7,COLOR_MAGENTA,COLOR_BLACK);
		init_pair(8,COLOR_RED,COLOR_BLACK);
		init_pair(9,COLOR_RED,COLOR_BLACK);
		init_pair(10,COLOR_RED,COLOR_BLACK);
		init_pair(11,COLOR_RED,COLOR_WHITE);
	}
}

void display_close() {
	endwin();
}

void display_plot(struct game *G) {
	unsigned int start_row = (LINES - G->rows)/2;
	unsigned int start_col = (COLS  - 2*G->cols)/2;

	erase();
	mvprintw(start_row-2,start_col-1,"MINES: %u/%u   DISPLAYED: %u/%u",G->flags,G->mines,G->displayed,G->rows*G->cols-G->mines);
	mvprintw(start_row + G->rows+1,start_col-1,"[Q]uit  [R]estart  [F]lag  [D]isplay  [E]xpand");
	display_border(G,start_row,start_col);
	display_world(G,start_row,start_col,0);
	refresh();
}

void display_gameover(struct game *G) {
	unsigned int start_row = (LINES - G->rows)/2;
	unsigned int start_col = (COLS - 2*G->cols)/2;
	char *str1 = "GAME OVER - YOU WIN!";
	char *str2 = "GAME OVER - YOU LOSE!";

	erase();
	mvprintw(start_row-2,start_col-1,"MINES: %u/%u   DISPLAYED: %u/%u",G->flags,G->mines,G->displayed,G->rows*G->cols-G->mines);
	display_border(G,start_row,start_col);
  display_world(G,start_row,start_col,1);
	mvprintw(start_row + G->rows+1,start_col-1,"[Q]uit  [R]estart");
	if(G->displayed == G->rows*G->cols-G->mines)
		//mvprintw(start_row+G->rows+3,start_col+(((int)2*G->cols-strlen(str1))/2),str1);
		mvprintw(start_row-3,start_col+(((int)2*G->cols-strlen(str1))/2),str1);
	else
		//mvprintw(start_row+G->rows+3,start_col+(((int)2*G->cols-strlen(str2))/2),str2);	
		mvprintw(start_row-3,start_col+(((int)2*G->cols-strlen(str2))/2),str2);
	refresh();
}

static void display_border(struct game *G, unsigned int start_row, unsigned int start_col) {
	unsigned int i;
	
	mvaddch(start_row-1,start_col-2,ACS_ULCORNER);
	mvaddch(start_row-1,start_col+2*G->cols,ACS_URCORNER);
	mvaddch(start_row+G->rows,start_col-2,ACS_LLCORNER);
	mvaddch(start_row+G->rows,start_col+2*G->cols,ACS_LRCORNER);

	for(i = 0; i < G->rows; i++) {
		mvaddch(start_row+i,start_col-2,ACS_VLINE);
    mvaddch(start_row+i,start_col+2*G->cols,ACS_VLINE);
	}

	for(i = 0; i <= 2*G->cols; i++) {
		mvaddch(start_row-1,start_col+i-1,ACS_HLINE);
		mvaddch(start_row+G->rows,start_col+i-1,ACS_HLINE);
	}
}

static void display_world(struct game *G, unsigned int start_row, unsigned int start_col, int gameover) {
	unsigned int i,j;

	for(i = 0; i < G->rows; i++)
		for(j = 0; j < G->cols; j++)
			switch(G->board[i][j]) {
				case UNKN_FREE:
					mvaddch(start_row+i,start_col+2*j,UNKN_SYMBOL); 
					break;
				case UNKN_MINE:
					if(gameover) {
						attron(COLOR_PAIR(10));
						mvaddch(start_row+i,start_col+2*j,MINE_SYMBOL);
						attroff(COLOR_PAIR(10));
					} else {
						mvaddch(start_row+i,start_col+2*j,UNKN_SYMBOL);
					} 
					break;
				case FLAG_FREE:
					mvaddch(start_row+i,start_col+2*j,FLAG_SYMBOL);
					break;
				case FLAG_MINE:
					if(gameover) {
						attron(COLOR_PAIR(10));
						mvaddch(start_row+i,start_col+2*j,MINE_SYMBOL);
						attroff(COLOR_PAIR(10));
					} else {
						mvaddch(start_row+i,start_col+2*j,FLAG_SYMBOL);
					}
					break;
				case MINE: 
					attron(COLOR_PAIR(11));
					mvaddch(start_row+i,start_col+2*j,MINE_SYMBOL); 
					attroff(COLOR_PAIR(11));
					break;
				case C0:
					mvaddch(start_row+i,start_col+2*j,' '); break;
				case C1: 
					attron(COLOR_PAIR(2));
					mvaddch(start_row+i,start_col+2*j,'1');
					attroff(COLOR_PAIR(2));
					break;
				case C2:
					attron(COLOR_PAIR(3));
					mvaddch(start_row+i,start_col+2*j,'2'); 
					attroff(COLOR_PAIR(3));
					break;
				case C3:
					attron(COLOR_PAIR(4));
					mvaddch(start_row+i,start_col+2*j,'3'); 
					attroff(COLOR_PAIR(4));
					break;
				case C4:
					attron(COLOR_PAIR(5));
					mvaddch(start_row+i,start_col+2*j,'4'); 
					attroff(COLOR_PAIR(5));
					break;
				case C5:
					attron(COLOR_PAIR(6));
					mvaddch(start_row+i,start_col+2*j,'5'); 
					attroff(COLOR_PAIR(6));
					break;
				case C6:
					attron(COLOR_PAIR(7));
					mvaddch(start_row+i,start_col+2*j,'6'); 
					attroff(COLOR_PAIR(7));
					break;
				case C7:
					attron(COLOR_PAIR(8));
					mvaddch(start_row+i,start_col+2*j,'7');
					attroff(COLOR_PAIR(8));
					break;
				case C8:
					attron(COLOR_PAIR(9));
					mvaddch(start_row+i,start_col+2*j,'8'); 
					attroff(COLOR_PAIR(9));
					break;
				default: break;
			}
		mvaddch(start_row+G->cursor_row,start_col+2*G->cursor_col-1,CURS_SYMBOL_LEFT);
		mvaddch(start_row+G->cursor_row,start_col+2*G->cursor_col+1,CURS_SYMBOL_RIGHT);

		//mvprintw(start_row + G->rows+2,start_col-1,"%d, %d",G->cursor_row,G->cursor_col);
}

int display_read(void) {
  return getch();
}
