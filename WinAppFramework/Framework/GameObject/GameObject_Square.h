#pragma once
#include "..\GameObjectBase.h"

class GameObject_Square : public GameObjectBase, public Render
{
public:
	GameObject_Square();
	~GameObject_Square();

	virtual void Rendering() override;

	void SetOriginToLeftTop(Vector2 position);
	void SetOriginToRightBottom(Vector2 position);
	void SetSquareSize(int width, int height);
	void SetColor(COLORREF RGB);
	BoundingBox GetBounds();

private:
	Vector2 originToLeftTop;
	Vector2 originToRightBottom;
	COLORREF color;
};
