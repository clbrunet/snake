#include <curses.h>

#include "snake/Game.hpp"

int main()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	refresh();

	Game game;
	game.play();

	getch();

	endwin();
	return 0;
}
