#include "snake/Vector2Int.hpp"

Vector2Int::Vector2Int() :
	x(0),
	y(0)
{
}

Vector2Int::Vector2Int(int x, int y) :
	x(x),
	y(y)
{
}

Vector2Int::Vector2Int(const Vector2Int& src) :
	x(src.x),
	y(src.y)
{
}

Vector2Int& Vector2Int::operator=(const Vector2Int& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vector2Int::~Vector2Int()
{
}

bool Vector2Int::operator==(const Vector2Int& rhs) const
{
	if (x == rhs.x && y == rhs.y) {
		return true;
	}
	return false;
}

bool Vector2Int::operator!=(const Vector2Int& rhs) const
{
	if (x != rhs.x || y != rhs.y) {
		return true;
	}
	return false;
}
