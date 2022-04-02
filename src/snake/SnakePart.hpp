#pragma once

#include <curses.h>

#include "snake/Vector2Int.hpp"

struct SnakePart
{
	Vector2Int position;
	chtype ch;

	SnakePart(const Vector2Int& position, chtype ch);
};
