#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <limits.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MINE 1
#define HIDDEN 2

typedef struct BOX{
	unsigned char *q;
	int row, column;
	int mines, totalcnt;
}BOX;

void createbox(BOX *, int, int);
int create_mines(BOX *, int, int, int);
WINDOW *w, *z; 

void print_usage(){
	printf("./a.out (no. of rows) (no. of columns)\n");
}


int main(int argc, char *argv[]){
	BOX p;
	int option = 0;
	while((option = getopt(argc, argv, "h::" )) != -1){
		switch(option){
			case 'h':
				print_usage();
				exit(0);
			default:
				break;
		}
	}

	int c, k = 10;
	int HEIGHT, WIDTH;	
	MEVENT event;

	srand(time(NULL));	 
	initscr();
	start_color();
	//nonl();
	clear();
	cbreak();
	noecho();

	if (argc >= 3) {
		HEIGHT = atoi(argv[1]);
		WIDTH = atoi(argv[2]);
	}
	
	if(argc < 3){
		HEIGHT = 9;
		WIDTH = 9;
	}
	w = newwin(HEIGHT+2, 2*WIDTH+2, 1, 0);
	
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

	attron(A_STANDOUT);
	mvprintw(0, 0, "Minesweeper");
	refresh();
	
	mvchgat(0, 0, -1, A_BOLD, 1, NULL);
	attroff(A_STANDOUT);
	refresh();

	createbox(&p, HEIGHT, WIDTH);
	create_mines(&p, WIDTH, HEIGHT, k);

	mousemask(ALL_MOUSE_EVENTS, NULL);
	refresh();

	while(1){
		if((c = getch()) == 'q')
			break;
		if(c == KEY_MOUSE){
			if(getmouse(&event) == OK){
				if((event.x > HEIGHT || (event.y > WIDTH)));
				mvprintw(event.y, event.x, "1");
				refresh();
			}
		}
	}

	mousemask(0,0);
	keypad(z, 0);
	delwin(w);
	free(p.q);
	endwin();
	return 0;
}
void createbox(BOX *p, int HEIGHT, int WIDTH){
	int i, j;
	p->column = HEIGHT;
	p->row = WIDTH;
	box(w, 0, 0);
	refresh();
	wrefresh(w);

	for(i = 1; i < p->column+1; i++){
		for(j = 0; j < p->row; j++){
			mvaddch((i + 1), (2 * j + 1), '.');
		}
	}
	refresh();	
}

int create_mines(BOX *p, int row, int column, int mines) {
	p->row = row;
	p->column = column;
	p->mines = mines;
	p->totalcnt = row * column;
	p->q = malloc(p->totalcnt);
	if(p->q == NULL) 
		return -1;
	memset(p->q, '0', p->totalcnt);
 
	while(mines--) {
		row = rand() % p->row;
		column = rand() % p->column;
		if(p->q[p->row * column + row] == MINE) {
			mines++;
			continue;
		}
		p->q[p->row * column + row] = MINE;
	}
	for(row = 0; row < p->totalcnt; row++)
		p->q[row] |= HIDDEN;
	return 0;
}
	
