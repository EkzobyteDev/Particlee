#pragma once
#include <SDL.h>

class vector2
{
	SDL_Point* point = nullptr;

public:
	float x, y;

	vector2();
	vector2(float x, float y);
	~vector2();

	float length();
	SDL_Point toSDL_Point();

	// Comparison
	bool operator==(const vector2& r);
	bool operator!=(const vector2& r);

	// Arithmetical
	vector2& operator+(const vector2& r);
	vector2& operator-(const vector2& r);
	vector2& operator*(float l);
	vector2& operator/(float l);

	void operator+=(const vector2& other);
	void operator-=(const vector2& other);
	void operator*=(float l);
	void operator/=(float l);
};