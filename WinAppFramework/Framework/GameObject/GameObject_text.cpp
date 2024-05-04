#include "GameObject.h"

//text obj :
GameObject_Text::GameObject_Text()
{
	text = nullptr;
	color = RGB(0, 0, 0);
}
GameObject_Text::~GameObject_Text()
{
	if (text != nullptr) delete text;
}
//오브젝트 랜더링시 호출되는 메서드
void GameObject_Text::Rendering()
{
	if (this->text == nullptr)
		return;

	COORD intPos = { 0,};
	intPos.X = (short)transform.position.X;
	intPos.Y = (short)transform.position.Y;
	this->Drawtext(intPos, this->text, color);
}
//문자열 필드 설정
void GameObject_Text::SetText(const char* string, int stringLen)
{
	if (text != nullptr) delete text;
	int arraySize = stringLen + 1;
	text = new char[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		text[i] = string[i];
	}
}
//문자 색깔 설정
void GameObject_Text::SetColor(COLORREF RGB)
{
	color = RGB;
}
