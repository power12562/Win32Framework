#include "GameObject_Line.h"

GameObject_Line::GameObject_Line() //持失切
{
	this->originToStartVertex = { -5, 0 };
	this->originToEndVertex = { 5, 0 };
	this->LineWidth = 5;
	this->color = RGB(0, 0, 0);
}

GameObject_Line::~GameObject_Line() //社瑚切
{

}

void GameObject_Line::Rendering()
{
	COORD startPos = { short(transform.position.X + originToStartVertex.X), short(transform.position.Y + originToStartVertex.Y)};
	COORD endPos = { short(transform.position.X + originToEndVertex.X), short(transform.position.Y + originToEndVertex.Y)};

	DrawLine(startPos, endPos, this->color, this->LineWidth);
}

void GameObject_Line::SetOriginToStartVertex(Vector2 position)
{
	originToStartVertex = position;
}

void GameObject_Line::SetOriginToEndVertex(Vector2 position)
{
	originToEndVertex = position;
}

void GameObject_Line::SetColor(COLORREF RGB)
{
	color = RGB;
}

void GameObject_Line::SetLineWidth(int Width)
{
	LineWidth = Width;
}