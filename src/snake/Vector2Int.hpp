#pragma once

struct Vector2Int
{
	int x;
	int y;

	Vector2Int();
	Vector2Int(int x, int y);
	Vector2Int(const Vector2Int& src);
	Vector2Int& operator=(const Vector2Int& rhs);
	~Vector2Int();

	bool operator==(const Vector2Int& rhs) const;
	bool operator!=(const Vector2Int& rhs) const;
};
