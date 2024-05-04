#include "GameObject.h"

GameObject_Polygon::GameObject_Polygon()
{
	color = RGB(0, 0, 0);
	vertexCount = 3;
	originToPoint = new POINT[vertexCount];

	originToPoint[0] = { 0, 50 };
	originToPoint[1] = {-58, -50 };
	originToPoint[2] = { 58, -50 };
}
GameObject_Polygon::~GameObject_Polygon()
{
	if(originToPoint != nullptr) delete[] originToPoint;
}

void GameObject_Polygon::Rendering()
{
	POINT* points = new POINT[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		points[i].x = LONG(transform.position.X + originToPoint[i].x);
		points[i].y = LONG(transform.position.Y + originToPoint[i].y);
	}
	DrawPolygon(points, vertexCount, color);

	delete[] points;
}

void GameObject_Polygon::SetOriginToPoints(POINT points[], int vertextCount)
{
	if (originToPoint != nullptr) delete[] originToPoint;

	this->vertexCount = vertextCount;

	originToPoint = new POINT[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		originToPoint[i] = points[i];
	}
}

void GameObject_Polygon::SetColor(COLORREF RGB)
{
	this->color = RGB;
}