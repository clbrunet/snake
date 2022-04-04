#include "snake/SnakePart.hpp"

SnakePart::SnakePart(const Vector2Int& position, chtype ch) :
	position(position),
	ch(ch)
{
}

SnakePart::SnakePart(const SnakePart& src) :
	position(src.position),
	ch(src.ch)
{
}

SnakePart& SnakePart::operator=(const SnakePart& rhs)
{
	position = rhs.position;
	ch = rhs.ch;
	return *this;
}

SnakePart::~SnakePart()
{
}
