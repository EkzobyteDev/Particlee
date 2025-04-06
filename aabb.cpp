#pragma once
#include "vector2.cpp"

class aabb
{
public:
	vector2 pos;
	vector2 size;

	aabb(float x0 = 0, float y0 = 0, float w = 0, float h = 0)
	{
		pos = vector2(x0, y0);
		size = vector2(w, h);
	}

	bool contains(vector2 point)
	{
		return (pos.x <= point.x && point.x < pos.x + size.x) && 
		       (pos.y <= point.y && point.y < pos.y + size.y); 
	}
};