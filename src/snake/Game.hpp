#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <curses.h>

#include "snake/Snake.hpp"

class Game
{
public:
	Game();
	Game(const Game& src);
	Game& operator=(const Game& rhs);
	~Game();

	static const int board_height;
	static const int board_width;

	const WINDOW* getWindow() const;
	void play();
private:

	WINDOW *window_;
	Snake snake_;
	Vector2Int fruit_position_;

	void newFruit();
	void draw() const;
};

#endif
