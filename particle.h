#pragma once
#include "vector2.cpp"

class particle
{
public:
	vector2 coordsOld;
	vector2 velocityOld;

	vector2 coords;
	vector2 velocity;

	float radius;
	float mass;
};