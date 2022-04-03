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
	bool getIsDead() const;

	void move(int input, const Vector2Int& fruit_position);

private:
	std::deque<SnakePart> parts_;
	Direction direction_;
	bool is_dead_;

	void processInput(int input);
	bool isNewHeadPositionDeath(const Vector2Int& new_pos) const;
};
