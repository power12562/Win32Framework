#pragma once
#include "..\GameObjectBase.h"

class GameObject_Polygon : public GameObjectBase, public Render
{
public:
	GameObject_Polygon();
	virtual ~GameObject_Polygon();

	virtual void Rendering() override;
	void SetOriginToPoints(POINT points[], int vertextCount);
	void SetColor(COLORREF RGB);

private:
	int vertexCount;
	POINT* originToPoint;
	COLORREF color;
};