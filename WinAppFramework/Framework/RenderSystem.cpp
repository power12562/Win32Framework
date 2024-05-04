#include "RenderSystem.h"
#include "WinApp.h"

#pragma comment(lib, "msimg32.lib")

//static field:
HWND Render::hWnd = NULL;
HINSTANCE Render::hInstance = NULL;

HDC Render::frontMemDC = NULL; 
HDC Render::backMemDC = NULL;
HBITMAP Render::backBitmap = NULL;

//static Method
void Render::InitRenderSystem() //정적 필드 초기화
{
	hWnd = WinApp::GetWinApp().GetWindow();

	hInstance = WinApp::GetWinApp().GetInstance();

	frontMemDC = GetDC(hWnd);

	backMemDC = CreateCompatibleDC(frontMemDC);

	backBitmap = CreateCompatibleBitmap(frontMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());

	SetStretchBltMode(backMemDC, COLORONCOLOR);
}
void Render::BeginDraw() //그릴 버퍼 선택
{
	ClearScreen();

	SelectObject(backMemDC, backBitmap);
}
void Render::EndDraw() //백 버퍼를 화면에 출력
{
	BitBlt(frontMemDC, 0, 0, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight(), backMemDC, 0, 0, SRCCOPY);
}
void Render::ClearScreen() //선택된 화면 하얀색으로 지운다
{
	PatBlt(backMemDC, 0, 0, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight(), WHITENESS);
}
void Render::FinalizeRenderSystem() //winapp종료시 렌더 시스템도 메모리 해제
{
	DeleteObject(backBitmap);

	DeleteDC(backMemDC);

	ReleaseDC(hWnd, frontMemDC);
}

Render::Render() 
{
	
}
Render::~Render()
{

}

//선택된 버퍼에 선을 그린다
void Render::DrawLine(COORD start, COORD end, COLORREF color, int PenWidth)
{
	PositionToScreenPos(start);
	PositionToScreenPos(end);

	HPEN hPen = CreatePen(PS_SOLID, PenWidth, color);

	HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

	MoveToEx(backMemDC, start.X, start.Y, NULL);

	LineTo(backMemDC, end.X, end.Y);

	SelectObject(backMemDC, hOldPen);

	DeleteObject(hPen);
}

//선택된 화면에 네모를 그린다.
void Render::DrawRect(HDC drawhdc, COORD LeftTop, COORD RightBottom, COLORREF color)
{
	PositionToScreenPos(LeftTop);
	PositionToScreenPos(RightBottom);

	HPEN hPen = CreatePen(PS_SOLID, 1, color);

	HPEN hOldPen = (HPEN)SelectObject(drawhdc, hPen);

	HBRUSH hBrush = CreateSolidBrush(color);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(drawhdc, hBrush);

	Rectangle(drawhdc, LeftTop.X, LeftTop.Y, RightBottom.X, RightBottom.Y);

	SelectObject(drawhdc, hOldPen);
	SelectObject(drawhdc, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}
void Render::DrawRect(COORD LeftTop, COORD RightBottom, COLORREF color)
{
	PositionToScreenPos(LeftTop);
	PositionToScreenPos(RightBottom);

	HPEN hPen = CreatePen(PS_SOLID, 1, color);

	HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

	HBRUSH hBrush = CreateSolidBrush(color);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

	Rectangle(backMemDC, LeftTop.X, LeftTop.Y, RightBottom.X, RightBottom.Y);

	SelectObject(backMemDC, hOldPen);
	SelectObject(backMemDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

//선택된 화면에 원을 그린다
void Render::DrawCircle(COORD DrawPos, int radius, COLORREF color)
{
	PositionToScreenPos(DrawPos);

	HPEN hPen = CreatePen(PS_SOLID, 1, color);

	HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

	HBRUSH hBrush = CreateSolidBrush(color);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

	Ellipse(backMemDC, DrawPos.X - radius, DrawPos.Y - radius, DrawPos.X + radius, DrawPos.Y + radius);

	SelectObject(backMemDC, hOldPen);
	SelectObject(backMemDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

//폴리곤 그리기
void Render::DrawPolygon(POINT points[], int count, COLORREF color)
{
	for (int i = 0; i < count; i++)
	{
		PositionToScreenPos(points[i]);
	}

	HPEN hPen = CreatePen(PS_SOLID, 1, color);

	HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

	HBRUSH hBrush = CreateSolidBrush(color);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

	Polygon(backMemDC, points, count);

	SelectObject(backMemDC, hOldPen);
	SelectObject(backMemDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

//텍스트 그리기
void Render::Drawtext(COORD position, const char* text, COLORREF color)
{
	PositionToScreenPos(position);

	SetTextColor(backMemDC, color);

	TextOutA(backMemDC, position.X, position.Y, text, (int)strlen(text));
}

//비트맵 로드해서 출력
void Render::DrawBitmap(COORD position, HBITMAP Hbitmap_load)
{
	PositionToScreenPos(position);

	HDC HDC_temp = CreateCompatibleDC(backMemDC);

	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	//해당 비트맵을 그린다
	SelectObject(HDC_temp, Hbitmap_load);

	//이미지 중심을 기준으로 원점 이동
	position.X -= short(bitmap_load.bmWidth / 2);
	position.Y -= short(bitmap_load.bmHeight / 2);
	BitBlt(backMemDC, position.X, position.Y, bitmap_load.bmWidth, bitmap_load.bmHeight, HDC_temp, 0, 0, SRCCOPY);

	//사용한 핸들 삭제
	DeleteDC(HDC_temp);
}

//크기 조정 후 출력
void Render::DrawBitmap_ReSize(COORD position, HBITMAP Hbitmap_load, float scaleWidth, float scaleHeight)
{
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다
	int ReSizeWidth = int(bitmap_load.bmWidth * scaleWidth);
	int ReSizeHeight = int(bitmap_load.bmHeight * scaleHeight);

	DrawBitmap_ReSize(position, Hbitmap_load, ReSizeWidth, ReSizeHeight);
}
void Render::DrawBitmap_ReSize(COORD position, HBITMAP Hbitmap_load, int ReSizeWidth, int ReSizeHeight)
{
	PositionToScreenPos(position);

	HDC HDC_temp = CreateCompatibleDC(backMemDC);

	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	//해당 비트맵을 그린다
	SelectObject(HDC_temp, Hbitmap_load);

	//이미지 중심을 기준으로 원점 이동
	position.X -= short(ReSizeWidth / 2);
	position.Y -= short(ReSizeHeight / 2);
	StretchBlt(backMemDC, position.X, position.Y, ReSizeWidth, ReSizeHeight, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, SRCCOPY);

	//사용한 핸들 삭제
	DeleteDC(HDC_temp);
}

//리소스 불러와서 투명도 조절하고 출력 해주기
void Render::DrawBitmap_AlphaBlend(COORD position, HBITMAP Hbitmap_load, float alpha, float scaleWidth, float scaleHeight)
{
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다
	int ReSizeWidth = int(bitmap_load.bmWidth * scaleWidth);
	int ReSizeHeight = int(bitmap_load.bmHeight * scaleHeight);

	DrawBitmap_AlphaBlend(position, Hbitmap_load, alpha, ReSizeWidth, ReSizeHeight);
}
void Render::DrawBitmap_AlphaBlend(COORD position, HBITMAP Hbitmap_load, float alpha, int ReSizeWidth, int ReSizeHeight)
{
	PositionToScreenPos(position);

	HDC HDC_temp = CreateCompatibleDC(backMemDC);

	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	//해당 비트맵을 그린다
	SelectObject(HDC_temp, Hbitmap_load);

	//이미지 중심을 기준으로 원점 이동
	position.X -= short(ReSizeWidth / 2);
	position.Y -= short(ReSizeHeight / 2);

	// BLENDFUNCTION 구조체
	BLENDFUNCTION bf = {0,};
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = int(255 * alpha); // 투명도(투명 0 - 불투명 255)
	AlphaBlend(
		backMemDC, position.X, position.Y, ReSizeWidth, ReSizeHeight,
		HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, bf);

	//사용한 핸들 삭제
	DeleteDC(HDC_temp);
}

//리소스 불러와서 원하는 색 지우고 출력 해주기
void Render::DrawBitmap_TransparentBlt(COORD position, HBITMAP Hbitmap_load, COLORREF BG_COLOR, float scaleWidth, float scaleHeight)
{
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다
	int ReSizeWidth = int(bitmap_load.bmWidth * scaleWidth);
	int ReSizeHeight = int(bitmap_load.bmHeight * scaleHeight);

	DrawBitmap_TransparentBlt(position, Hbitmap_load, BG_COLOR, ReSizeWidth, ReSizeHeight);
}
void Render::DrawBitmap_TransparentBlt(COORD position, HBITMAP Hbitmap_load, COLORREF BG_COLOR, int ReSizeWidth, int ReSizeHeight)
{
	PositionToScreenPos(position);

	HDC HDC_temp = CreateCompatibleDC(backMemDC);

	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	//해당 비트맵을 그린다
	SelectObject(HDC_temp, Hbitmap_load);

	//이미지 중심을 기준으로 원점 이동
	position.X -= short(ReSizeWidth / 2);
	position.Y -= short(ReSizeHeight / 2);

	SelectObject(HDC_temp, Hbitmap_load);

	TransparentBlt(
		backMemDC, position.X, position.Y, ReSizeWidth, ReSizeHeight,
		HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, BG_COLOR);

	//사용한 핸들 삭제
	DeleteDC(HDC_temp);
}

void Render::DrawBitmap_AlphaAndTransparent(COORD position, HBITMAP Hbitmap_load, float alpha, COLORREF BG_COLOR, float scaleWidth, float scaleHeight)
{
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다
	int ReSizeWidth = int(bitmap_load.bmWidth * scaleWidth);
	int ReSizeHeight = int(bitmap_load.bmHeight * scaleHeight);

	DrawBitmap_AlphaAndTransparent(position, Hbitmap_load, alpha, BG_COLOR, ReSizeWidth, ReSizeHeight);
}

void Render::DrawBitmap_AlphaAndTransparent(COORD position, HBITMAP Hbitmap_load, float alpha, COLORREF BG_COLOR, int ReSizeWidth, int ReSizeHeight)
{
	PositionToScreenPos(position);

	HDC HDC_Alpha = CreateCompatibleDC(backMemDC);
	HBITMAP HBITMAP_Alpha = CreateCompatibleBitmap(frontMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_Alpha, HBITMAP_Alpha);

	HDC HDC_temp = CreateCompatibleDC(backMemDC);
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(Hbitmap_load, sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	//해당 비트맵을 그린다
	SelectObject(HDC_temp, Hbitmap_load);

	//이미지 중심을 기준으로 원점 이동
	position.X -= short(ReSizeWidth / 2);
	position.Y -= short(ReSizeHeight / 2);

	BitBlt(HDC_Alpha, 0, 0, ReSizeWidth, ReSizeWidth, backMemDC, position.X, position.Y, SRCCOPY);
	TransparentBlt(
		HDC_Alpha, 0, 0, ReSizeWidth, ReSizeWidth,
		HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, BG_COLOR);
	// BLENDFUNCTION 구조체
	BLENDFUNCTION bf{ 0, };
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = int(255 * alpha); // 투명도(투명 0 - 불투명 255)
	AlphaBlend(
		backMemDC, position.X, position.Y, ReSizeWidth, ReSizeWidth,
		HDC_Alpha, 0, 0, ReSizeWidth, ReSizeWidth, bf);

	//사용한 핸들 삭제
	DeleteDC(HDC_temp);
	DeleteDC(HDC_Alpha);
	DeleteObject(HBITMAP_Alpha);
}

void Render::DrawFont(RECT& rc, const wchar_t* str, int uFormat)
{
	DrawText(backMemDC, str, -1, &rc, uFormat);
}


void Render::PositionToScreenPos(COORD& position)
{
	position.Y = WinApp::GetWinApp().GetClientHeight() - position.Y;
}
void Render::PositionToScreenPos(POINT& point)
{
	point.y = WinApp::GetWinApp().GetClientHeight() - point.y;
}