#pragma once
#include <math.h>
#include <iostream>

class vector2
{
public:
	float x, y;

	vector2(float x = 0, float y = 0)
	{
		this->x = x;
		this->y = y;
	}

	static vector2& zero()
	{
		vector2 z(0, 0);
		return z;
	}
	static vector2& one()
	{
		vector2 o(1, 1);
		return o;
	}

	inline float sqrlen()
	{
		return x*x + y*y;
	}
	inline float length()
	{
		return sqrtf(sqrlen());
	}

	// Comparison
	inline bool operator==(vector2& rhs)
	{
		return this->x == rhs.x && this->y == rhs.y;
	}
	inline bool operator!=(vector2& rhs)
	{
		return !(*this == rhs);
	}

	// Arithmetical
	inline vector2& operator+=(const vector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	inline vector2& operator-=(const vector2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	inline vector2& operator*=(const float l)
	{
		this->x *= l;
		this->y *= l;
		return *this;
	}
	inline vector2& operator/=(const float l)
	{
		this->x /= l;
		this->y /= l;
		return *this;
	}
};

inline vector2 operator+(vector2 lhs, const vector2& rhs)
{
	lhs += rhs;
	return lhs;
}
inline vector2 operator-(vector2 lhs, const vector2& rhs)
{
	lhs -= rhs;
	return lhs;
}
inline vector2 operator*(vector2 lhs, const vector2& rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	return lhs;
}
inline vector2 operator/(vector2 lhs, const vector2& rhs)
{
	lhs.x /= rhs.x;
	lhs.y /= rhs.y;
	return lhs;
}

inline vector2 operator+(vector2 lhs, const float l)
{
	lhs.x += l;
	lhs.y += l;
	return lhs;
}
inline vector2 operator-(vector2 lhs, const float l)
{
	return lhs + (-l);
}
inline vector2 operator*(vector2 lhs, const float l)
{
	lhs *= l;
	return lhs;
}
inline vector2 operator/(vector2 lhs, const float l)
{
	return lhs * (1/l);
}