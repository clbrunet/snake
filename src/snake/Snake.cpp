#include <curses.h>
#include <cassert>

#include "snake/Game.hpp"
#include "snake/Snake.hpp"

Snake::Snake() :
	parts_(),
	direction_(Direction::Right),
	is_dead_(false)
{
	assert(Game::board_width > 3);
	assert(Game::board_height > 3);

	for (int i = 1; i <= 3; i++) {
		parts_.push_front(SnakePart(Vector2Int(i, Game::board_height / 2), ACS_HLINE));
	}
}

Snake::Snake(const Snake& src) :
	parts_(src.parts_),
	direction_(src.direction_),
	is_dead_(false)
{
}

Snake& Snake::operator=(const Snake& rhs)
{
	parts_ = rhs.parts_;
	direction_ = rhs.direction_;
	is_dead_ = rhs.is_dead_;
	return *this;
}

Snake::~Snake()
{
}

const std::deque<SnakePart>& Snake::getParts() const
{
	return parts_;
}

Direction Snake::getDirection() const
{
	return direction_;
}

bool Snake::getIsDead() const
{
	return is_dead_;
}

void Snake::move(int input, const Vector2Int& fruit_position)
{
	processInput(input);

	Vector2Int new_head_pos(parts_.front().position);
	chtype head_ch;
	switch (direction_) {
		case Direction::Up:
			new_head_pos.y--;
			head_ch = ACS_VLINE;
			break;
		case Direction::Down:
			new_head_pos.y++;
			head_ch = ACS_VLINE;
			break;
		case Direction::Right:
			new_head_pos.x++;
			head_ch = ACS_HLINE;
			break;
		case Direction::Left:
			new_head_pos.x--;
			head_ch = ACS_HLINE;
			break;
	}
	if (isNewHeadPositionDeath(new_head_pos) == false) {
		is_dead_ = true;
		return;
	}
	parts_.push_front(SnakePart(new_head_pos, head_ch));
	if (new_head_pos == fruit_position) {
		return;
	}
	parts_.pop_back();
}

void Snake::processInput(int input)
{
	SnakePart& head = parts_.front();

	switch (input) {
		case KEY_UP:
			if (direction_ == Direction::Right || direction_ == Direction::Left) {
				if (direction_ == Direction::Right) {
					head.ch = ACS_LRCORNER;
				} else {
					head.ch = ACS_LLCORNER;
				}
				direction_ = Direction::Up;
			}
			break;
		case KEY_DOWN:
			if (direction_ == Direction::Right || direction_ == Direction::Left) {
				if (direction_ == Direction::Right) {
					head.ch = ACS_URCORNER;
				} else {
					head.ch = ACS_ULCORNER;
				}
				direction_ = Direction::Down;
			}
			break;
		case KEY_RIGHT:
			if (direction_ == Direction::Up || direction_ == Direction::Down) {
				if (direction_ == Direction::Up) {
					head.ch = ACS_ULCORNER;
				} else {
					head.ch = ACS_LLCORNER;
				}
				direction_ = Direction::Right;
			} 
			break;
		case KEY_LEFT:
			if (direction_ == Direction::Up || direction_ == Direction::Down) {
				if (direction_ == Direction::Up) {
					head.ch = ACS_URCORNER;
				} else {
					head.ch = ACS_LRCORNER;
				}
				direction_ = Direction::Left;
			}
			break;
	}
}

bool Snake::isNewHeadPositionDeath(const Vector2Int& new_pos) const
{
	if (new_pos.x <= 0 || new_pos.y <= 0) {
		return false;
	}
	if (new_pos.x > Game::board_width || new_pos.y > Game::board_height) {
		return false;
	}
	for (std::deque<SnakePart>::const_iterator cit = parts_.cbegin();
			cit != parts_.cend() - 1; ++cit) {
		if (new_pos == cit->position) {
			return false;
		}
	}
	return true;
}
