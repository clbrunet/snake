#include <curses.h>
#include <cstring>

#include "snake/Game.hpp"

void mvaddstrCentered(int y, const char *str)
{
	mvaddstr(y, COLS / 2 - strlen(str) / 2, str);
}

int main()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	refresh();

	Game game;

	mvaddstrCentered(getbegy(game.getWindow()) - 1, "Press a key to start");
	getch();
	erase();
	refresh();

	game.play();

	mvaddstrCentered(getbegy(game.getWindow()) - 1, "Press a key to quit");
	getch();

	endwin();
	return 0;
}
