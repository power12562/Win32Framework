#pragma once
#include "..\GameObjectBase.h"

class GameObject_Circle : public GameObjectBase, public Render
{
public:
	GameObject_Circle();
	~GameObject_Circle();

	void Rendering();
	void SetRadious(int radius);
	void SetColor(COLORREF RGB);

private:
	int radius;
	COLORREF color;
};