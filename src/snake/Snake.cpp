#include <curses.h>

#include "snake/Snake.hpp"

Snake::Snake() :
	parts_(),
	direction_(Direction::Right)
{
	parts_.push_back(SnakePart(Vector2Int(3, 7), ACS_HLINE)); // TODO: hardcoded value
	parts_.push_back(SnakePart(Vector2Int(2, 7), ACS_HLINE)); // TODO: hardcoded value
	parts_.push_back(SnakePart(Vector2Int(1, 7), ACS_HLINE)); // TODO: hardcoded value
}

Snake::Snake(const Snake& src) :
	parts_(src.parts_),
	direction_(src.direction_)
{
}

Snake& Snake::operator=(const Snake& rhs)
{
	parts_ = rhs.parts_;
	direction_ = rhs.direction_;
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

int Snake::move(int input, const Vector2Int& fruit_position)
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
	Vector2Int new_head_pos(head.position);
	chtype ch;
	switch (direction_) {
		case Direction::Up:
			new_head_pos.y--;
			ch = ACS_VLINE;
			break;
		case Direction::Down:
			new_head_pos.y++;
			ch = ACS_VLINE;
			break;
		case Direction::Right:
			new_head_pos.x++;
			ch = ACS_HLINE;
			break;
		case Direction::Left:
			new_head_pos.x--;
			ch = ACS_HLINE;
			break;
	}
	if (checkNewHeadPosition(new_head_pos) == -1) {
		return -1;
	}
	parts_.push_front(SnakePart(new_head_pos, ch));
	if (new_head_pos == fruit_position) {
		return 1;
	}
	parts_.pop_back();
	return 0;
}

int Snake::checkNewHeadPosition(const Vector2Int& new_pos) const
{
	if (new_pos.x <= 0 || new_pos.y <= 0) {
		return -1;
	}
	if (new_pos.x > 17 || new_pos.y > 15) {
		return -1;
	}
	for (std::deque<SnakePart>::const_iterator cit = parts_.cbegin();
			cit != parts_.cend() - 1; ++cit) {
		if (new_pos == cit->position) {
			return -1;
		}
	}
	return 0;
}
