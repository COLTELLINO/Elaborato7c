CFLAG = -Wall -pedantic -Wno-comment -O3 -std=c89
 
all: minesweeper

board.o: board.h board.c
	gcc $(CFLAG) -c board.c

game.o: game.h game.c
	gcc $(CFLAG) -c game.c

display.o: display.h display.c
	gcc $(CFLAG) -c display.c

minesweeper: board.h game.h display.h board.o game.o display.o main.c
	gcc $(CFLAG) -lcurses board.o game.o display.o main.c -o minesweeper

clean:
	rm -rf *.o minesweeper 
