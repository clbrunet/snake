#ifndef SNAKE_SNAKEPART_HPP
#define SNAKE_SNAKEPART_HPP

#include <curses.h>

#include "snake/Vector2Int.hpp"

struct SnakePart
{
	Vector2Int position;
	chtype ch;

	SnakePart(const Vector2Int& position, chtype ch);
	SnakePart(const SnakePart& src);
	SnakePart& operator=(const SnakePart& rhs);
	~SnakePart();
};

#endif
