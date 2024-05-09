#include "GameObject_Square.h"

GameObject_Square::GameObject_Square()
{
	this->originToLeftTop = { -10, -10 };
	this->originToRightBottom = { 10, 10 };
	this->color = RGB(0, 0, 0);
}
GameObject_Square::~GameObject_Square()
{


}
void GameObject_Square::Rendering()
{
	COORD CD_LeftTop = { 0, }, CD_RightBottom = { 0, };
	COORD CD_Pos = { (short)transform.position.X, (short)transform.position.Y };

	CD_LeftTop.X = short(CD_Pos.X + originToLeftTop.X);
	CD_LeftTop.Y = short(CD_Pos.Y + originToLeftTop.Y);
	CD_RightBottom.X = short(CD_Pos.X + originToRightBottom.X);
	CD_RightBottom.Y = short(CD_Pos.Y + originToRightBottom.Y);

	DrawRect(CD_LeftTop, CD_RightBottom, color);
}

void GameObject_Square::SetOriginToLeftTop(Vector2 position)
{
	originToLeftTop = position;
}

void GameObject_Square::SetOriginToRightBottom(Vector2 position)
{
	originToRightBottom = position;
}

void GameObject_Square::SetSquareSize(int width, int height)
{
	int halfWidth = width / 2;
	int halfheight = height / 2;
	Vector2 LeftTop = { (float)-halfWidth,  (float)halfheight};
	Vector2 RightBottom = { (float)halfWidth,  (float)-halfheight};

	SetOriginToLeftTop(LeftTop);
	SetOriginToRightBottom(RightBottom);
}

void GameObject_Square::SetColor(COLORREF RGB)
{
	this->color = RGB;
}

BoundingBox GameObject_Square::GetBounds()
{
	BoundingBox bounds = {0, };
	bounds.LefTop.X = transform.position.X + originToLeftTop.X;
	bounds.LefTop.Y = transform.position.Y + originToLeftTop.Y;

	bounds.RightBottom.X = transform.position.X + originToRightBottom.X;
	bounds.RightBottom.Y = transform.position.Y + originToRightBottom.Y;

	bounds.Size.X = originToRightBottom.X - originToLeftTop.X;
	bounds.Size.Y = originToLeftTop.Y - originToRightBottom.Y;
	
	return bounds;
}