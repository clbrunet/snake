#pragma once

#include <curses.h>

#include "snake/Snake.hpp"

class Game
{
public:
	Game();
	Game(const Game& src);
	Game& operator=(const Game& rhs);
	~Game();

	const WINDOW* getWindow() const;
	void play();
private:
	static const int height;
	static const int width;

	WINDOW *window_;
	Snake snake_;
	Vector2Int fruit_position_;

	void newFruit();
	void draw() const;
};
