#pragma once
#include "..\GameObjectBase.h"

class GameObject_Line : public GameObjectBase, public Render
{
public:
	GameObject_Line();
	~GameObject_Line();

	virtual void Rendering() override;
	void SetOriginToStartVertex(Vector2 position);
	void SetOriginToEndVertex(Vector2 position);
	void SetColor(COLORREF RGB);
	void SetLineWidth(int Width);

private:
	Vector2 originToStartVertex;
	Vector2 originToEndVertex;
	COLORREF color;
	int LineWidth;
};