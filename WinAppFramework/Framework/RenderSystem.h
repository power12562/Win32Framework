#pragma once
#include <Windows.h>

class Render
{
public:
	static void InitRenderSystem();
	static void BeginDraw();
	static void EndDraw();
	static void FinalizeRenderSystem();

	virtual void Rendering() = 0;

	Render();
	~Render();

	void PositionToScreenPos(COORD& position); //월드 좌표를 화면 좌표로 변환해준다.
	void PositionToScreenPos(POINT& point);

protected:
	void DrawLine(COORD start, COORD end, COLORREF color, int PenWidth);

	void DrawRect(HDC drawhdc, COORD LeftTop, COORD RightBottom, COLORREF color);
	void DrawRect(COORD LeftTop, COORD RightBottom, COLORREF color);

	void DrawCircle(COORD DrawPos, int radius, COLORREF color);

	void DrawPolygon(POINT points[], int count, COLORREF color);

	void Drawtext(COORD position, const char* text, COLORREF color);

	void DrawBitmap(COORD position, HBITMAP Hbitmap_load);

	void DrawBitmap_ReSize(COORD position, HBITMAP Hbitmap_load, float scaleWidth, float scaleHeight);
	void DrawBitmap_ReSize(COORD position, HBITMAP Hbitmap_load, int ReSizeWidth, int ReSizeHeight);

	void DrawBitmap_AlphaBlend(COORD position, HBITMAP Hbitmap_load, float alpha, float scaleWidth = 1.0f, float scaleHeight = 1.0f);
	void DrawBitmap_AlphaBlend(COORD position, HBITMAP Hbitmap_load, float alpha, int ReSizeWidth, int ReSizeHeight);

	void DrawBitmap_TransparentBlt(COORD position, HBITMAP Hbitmap_load, COLORREF BG_COLOR, float scaleWidth = 1.0f, float scaleHeight = 1.0f);
	void DrawBitmap_TransparentBlt(COORD position, HBITMAP Hbitmap_load, COLORREF BG_COLOR, int ReSizeWidth, int ReSizeHeight);

	void DrawBitmap_AlphaAndTransparent(COORD position, HBITMAP Hbitmap_load, float alpha, COLORREF BG_COLOR, float scaleWidth = 1.0f, float scaleHeight = 1.0f);
	void DrawBitmap_AlphaAndTransparent(COORD position, HBITMAP Hbitmap_load, float alpha, COLORREF BG_COLOR, int ReSizeWidth, int ReSizeHeight);

	void DrawFont(RECT& rc, const wchar_t* wstr, int uFormat = NULL);

	static void ClearScreen();

	static HWND hWnd;
	static HINSTANCE hInstance;

	static HDC frontMemDC; //앞 버퍼
	static HDC backMemDC; //뒤 버퍼
	static HBITMAP backBitmap;
private:
};





