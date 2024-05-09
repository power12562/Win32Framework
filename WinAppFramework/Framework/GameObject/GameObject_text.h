#pragma once
#include "..\GameObjectBase.h"

class GameObject_Text : public GameObjectBase, public Render
{
public:
	GameObject_Text();
	virtual ~GameObject_Text();

	virtual void Rendering() override;

	void SetText(const char* string, int stringLen);
	void SetColor(COLORREF RGB);

private:
	char* text;
	COLORREF color;
};