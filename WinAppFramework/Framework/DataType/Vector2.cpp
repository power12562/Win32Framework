#include <math.h>
#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	this->X = x;
	this->Y = y;
}

Vector2::Vector2(double x, double y)
{
	this->X = (float)x;
	this->Y = (float)y;
}

Vector2::Vector2(int x, int y)
{
	this->X = float(x);
	this->Y = float(y);
}

Vector2::Vector2(const Vector2& other)
{
	this->X = other.X;
	this->Y = other.Y;	
}

Vector2 Vector2::Lerp(Vector2 startPos, Vector2 EndPos, float t)
{
	Vector2 Lerp = { (1.f - t) * startPos.X + t * EndPos.X, (1.f - t) * startPos.Y + t * EndPos.Y };
	
	return Lerp;
}

float Vector2::Magnitude()
{
	float magnitude = sqrtf(X * X + Y * Y);
	return magnitude;
}
Vector2 Vector2::Normalized()
{
	Vector2 normal = { float(X / Magnitude()) , float(Y / Magnitude()) };
	return normal;
}

Vector2 Vector2::operator*(const float scala) const
{
	Vector2 value = {this->X, this->Y};
	value.X *= scala;
	value.Y *= scala;

	return value;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->X += other.X;
	this->Y += other.Y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	this->X -= other.X;
	this->Y -= other.Y;

	return *this;
}

Vector2 Vector2::operator+(const Vector2 & other)
{
	Vector2 sum = { 0, 0 };
	sum.X = this->X + other.X;
	sum.Y = this->Y + other.Y;

	return sum;
}

Vector2 Vector2::operator-(const Vector2& other)
{
	Vector2 sub = { 0, 0 };
	sub.X = this->X - other.X;
	sub.Y = this->Y - other.Y;

	return sub;
}
