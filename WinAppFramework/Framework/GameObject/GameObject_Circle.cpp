#include "GameObject_Circle.h"

GameObject_Circle::GameObject_Circle()
{
	radius = 5;
	color = RGB(0,0,0);
}

GameObject_Circle::~GameObject_Circle()
{
}

void GameObject_Circle::Rendering()
{
	COORD int_pos = {0,};
	int_pos.X = (short)transform.position.X;
	int_pos.Y = (short)transform.position.Y;
	DrawCircle(int_pos, radius, color);
}

void GameObject_Circle::SetRadious(int radius)
{
	this->radius = radius;
}

void GameObject_Circle::SetColor(COLORREF RGB)
{
	this->color = RGB;
}