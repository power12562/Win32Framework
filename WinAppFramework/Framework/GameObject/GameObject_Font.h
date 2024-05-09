#pragma once
#include "..\GameObjectBase.h"

class GameObject_Font : public GameObjectBase, public Render
{
public:
	GameObject_Font();
	virtual ~GameObject_Font();

	virtual void Rendering() override;

	unsigned int uFormat = NULL;

	HFONT hFont;

	void SetPos(Vector2 pos);
	Vector2 GetPos() const;

	void SetSize(COORD Size);
	COORD GetSize() const { return size; }

	RECT GetRect() const { return rect; }

	void SetText(const wchar_t* sting);

private:

	COORD size;
	RECT rect;
	wString string;

	void ReAdjustRect();
};