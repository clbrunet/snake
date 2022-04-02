#pragma once

#include <deque>

#include "snake/SnakePart.hpp"

enum class Direction
{
	Up,
	Down,
	Right,
	Left
};

class Snake
{
public:
	Snake();
	Snake(const Snake& src);
	Snake& operator=(const Snake& rhs);
	~Snake();

	const std::deque<SnakePart>& getParts() const;
	Direction getDirection() const;

	int move(int input, const Vector2Int& fruit_position);
	int checkNewHeadPosition(const Vector2Int& new_pos) const;

private:
	std::deque<SnakePart> parts_;
	Direction direction_;
};
