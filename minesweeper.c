#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#define WIDTH 10
#define HEIGHT 10

void print_usage(){
	printf("Implementation of minesweeper game\n");
}

int main(int argc, char *argv[]){

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

	WINDOW *w, *z;
	int x, y, i, j;
	int c, m;
	mmask_t old;
	unsigned short flag;
	int mines[HEIGHT][WIDTH];
	
	MEVENT event;

	initscr();
	start_color();
	clear();
	cbreak();
	noecho();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

	x = (COLS-WIDTH)/2;
	y = (LINES-HEIGHT)/2;

	w = newwin(HEIGHT, WIDTH, 1, 0);
	z = newwin(HEIGHT+1, WIDTH, 1, 0);

	box(w, 0, 0);
	refresh();
	wrefresh(w);

	attron(A_STANDOUT);
	mvprintw(0, 0, "Minesweeper");
	refresh();

	mvchgat(0, 0, -1, A_BOLD, 1, NULL);
	attroff(A_STANDOUT);
	refresh();

	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, 0);
	
	
	for(i = 1; i < HEIGHT - 1; i++){
		for(j = 2; j < WIDTH; j++){
			mines[i][j] = rand()%10;
			m = mines[i][j];
			
		}
	}
	//refresh();
	

	for(i = 1; i < HEIGHT - 1; i++){
		for(j = 2; j < WIDTH; j++){
			mvaddch(j, i, '.');
		}
	}
	//refresh();

	while((c = getch())!= 'q'){
		if(c == KEY_MOUSE){
			if(getmouse(&event) == OK){
				if(event.x > HEIGHT || event.y > WIDTH)
					continue;
				mvprintw(event.y, event.x, "1");
				refresh();
				//i++;
				//j++;
			}
		}
		
	}
	keypad(z, 0);
	mousemask(0, 0);
	delwin(w);
	endwin();
	return 0;
}

