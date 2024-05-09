#include "GameObject_Font.h"

GameObject_Font::GameObject_Font()
{
	hFont = NULL;
	size = { 0, };
	rect = { 0, };
}

GameObject_Font::~GameObject_Font()
{
	DeleteObject(hFont);
}

void GameObject_Font::SetPos(Vector2 pos)
{
	this->transform.position = pos;
	ReAdjustRect();
}
Vector2 GameObject_Font::GetPos() const
{
	return this->transform.position;
}


void GameObject_Font::SetSize(COORD Size)
{
	this->size = Size;
	ReAdjustRect();
}

void GameObject_Font::SetText(const wchar_t* sting)
{
	this->string = sting;
}

void GameObject_Font::ReAdjustRect()
{
	COORD intPos = { (short)transform.position.X, (short)transform.position.Y };
	PositionToScreenPos(intPos);
	rect.left = LONG(intPos.X - size.X / 2.f);
	rect.right = LONG(intPos.X + size.X / 2.f);
	rect.top = LONG(intPos.Y - size.Y / 2.f);
	rect.bottom = LONG(intPos.Y + size.Y / 2.f);
}

void GameObject_Font::Rendering()
{
	HFONT hOldFont = (HFONT)SelectObject(backMemDC, hFont);

	DrawFont(rect, string.GetString(), uFormat);

	SelectObject(backMemDC, hOldFont);
}