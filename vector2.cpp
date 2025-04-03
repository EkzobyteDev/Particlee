#include "vector2.h"
#include <math.h>
#include <iostream>


vector2::vector2() { x = 0; y = 0; }
vector2::vector2(float x, float y) { this->x = x; this->y = y; }
vector2::~vector2() { delete point; }

float vector2::length() { return sqrtf(x*x + y*y); }
SDL_Point vector2::toSDL_Point()
{
	if (point == nullptr){ point = new SDL_Point(); }
	point->x = round(x);
	point->y = round(y);
	return *point;
}

// Comparison
bool vector2::operator==(const vector2& r) { return this->x == r.x && this->y == r.y; }
bool vector2::operator!=(const vector2& r) { return !(*this == r); }

// Arithmetical
vector2& vector2::operator+(const vector2& r) { vector2 temp(this->x + r.x, this->y + r.y); return temp; }
vector2& vector2::operator-(const vector2& r) { return *this + vector2(-r.x, -r.y); }
vector2& vector2::operator*(float l) { vector2 temp(this->x * l, this->y * l); return temp; }
vector2& vector2::operator/(float l) { return *this * (1/l); }

void vector2::operator+=(const vector2& r) { this->x = this->x + r.x; this->y = this->y + r.y; }
void vector2::operator-=(const vector2& r) { this->x = this->x - r.x; this->y = this->y - r.y; }
void vector2::operator*=(float l) { this->x = this->x * l; this->y = this->y * l; }
void vector2::operator/=(float l) { this->x = this->x / l; this->y = this->y / l; }
