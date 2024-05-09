#include "GameObject_Sprite.h"
#include "..\WinApp.h"
#include <math.h>
#include <float.h>
#include "..\DataType\Collision.h"
#include "..\DataType\Mathf.h"

GameObject_Sprite::GameObject_Sprite()
{
	this->Hbitmap = NULL;
	
	this->angle = 0;
	for (int i = 0; i < 4; i++)
	{
		this->BitMapVertexPoint[i] = Vector2{0, 0};
	}
	this->SetAngle(angle);

	this->reSizeWidth = 0;
	this->reSizeHeight = 0;

	this->Alpha = 1.0f;

	this->crTransparent = 0;

	this->bitflag = 0;
}

GameObject_Sprite::~GameObject_Sprite()
{
	if (this->Hbitmap != NULL) DeleteObject(Hbitmap);
}

GameObject_Sprite& GameObject_Sprite::operator=(const GameObject_Sprite&)
{
	return *this;
}

//public:
void GameObject_Sprite::Rendering()
{
	COORD int_pos = { short(transform.position.X), short(transform.position.Y) };
	switch (this->bitflag)
	{
		// Rescale | Resize | AlphaBlend | Transparent 
	case 0b1111:
	case 0b0111:
	case 0b1011:
	case 0b0011:
		DrawBitmap_AlphaAndTransparent();
		break;

		//AlphaBlend
	case 0b1110:
	case 0b0110:
	case 0b1010:
	case 0b0010:
		DrawBitmap_AlphaBlend();
		break;

		//Transparent
	case 0b1101:
	case 0b0101:
	case 0b1001:
	case 0b0001:
		DrawBitmap_TransparentBlt();
		break;

		//ReSize, ReScale
	default:
		DrawBitmap();
		break;
	}	
}

void GameObject_Sprite::SetAngle(float angle)
{
	this->angle = angle;

	UpdateBitMapVertexPoint();
}

float GameObject_Sprite::GetRadianAngle()
{
	float angle = this->angle;
	while (angle >= 360)
	{
		angle -= 360;
	}
	while (angle < 0)
	{
		angle += 360;
	}
	float radianAngle = angle / 180.0f * Mathf::pi;
	return radianAngle;
}
Vector2 GameObject_Sprite::GetDir()
{
	float radianAngle = GetRadianAngle();
	Vector2 dir = { cosf(radianAngle), sinf(radianAngle) };
	return dir;
}

void GameObject_Sprite::Loadbmp(const char* path)
{
	HINSTANCE hInstance = WinApp::GetWinApp().GetInstance();

	if (this->Hbitmap != NULL)
	{
		DeleteObject(Hbitmap); //원래 있던 비트맵은 삭제
	}
	this->Hbitmap = (HBITMAP)LoadImageA(
		hInstance, path, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

	UpdateBitMapVertexPoint();
}

HBITMAP GameObject_Sprite::GetHbitmap()
{
	if (Hbitmap == NULL) return NULL;
	else  return Hbitmap;
}
void GameObject_Sprite::ReleasebitMap()
{
	if (this->Hbitmap != NULL)
	{
		DeleteObject(Hbitmap); //원래 있던 비트맵은 삭제
	}
	this->Hbitmap = NULL;	
}

void GameObject_Sprite::SetReSize(int ReSizeWidth, int ReSizeHeight)
{
	this->reSizeWidth = ReSizeWidth;
	this->reSizeHeight = ReSizeHeight;

	this->SetEnableFlag(FlagTable::ReSize, true);

	UpdateBitMapVertexPoint();
}
COORD GameObject_Sprite::GetReSize()
{
	COORD Size = { (short)this->reSizeWidth, (short)this->reSizeHeight };
	return Size;
}

void GameObject_Sprite::SetAlpha(float alpha)
{
	this->Alpha = alpha;
	this->SetEnableFlag(FlagTable::Alpha, true);
}
float GameObject_Sprite::GetAlpha()
{
	return this->Alpha;
}

void GameObject_Sprite::SetTrColor(COLORREF RGB)
{
	this->crTransparent = RGB;
	this->SetEnableFlag(FlagTable::Transparent, true);
}
COLORREF GameObject_Sprite::GetTrColor()
{
	return this->crTransparent;
}

void GameObject_Sprite::SetEnableFlag(FlagTable flag, bool isEnable)
{
	short key = (short)flag;
	if (isEnable) 
		this->bitflag |= key;
	else		
		this->bitflag &= (~key);
}
bool GameObject_Sprite::GetEnableFlag(FlagTable flag)
{
	bool isEnable = this->bitflag & (short)flag;
	return isEnable;
}

BoundingBox GameObject_Sprite::GetBounds()
{
	UpdateBitMapVertexPoint();

	const int pointSize = 4;

	//포인트 위치에 따른 bounding box 크기 계산
	Vector2 min = { FLT_MAX, FLT_MAX };
	Vector2 max = { FLT_MIN, FLT_MIN };
	for (int i = 0; i < pointSize; i++)
	{
		if (BitMapVertexPoint[i].X < min.X) min.X = BitMapVertexPoint[i].X;
		if (BitMapVertexPoint[i].Y < min.Y) min.Y = BitMapVertexPoint[i].Y;

		if (BitMapVertexPoint[i].X > max.X) max.X = BitMapVertexPoint[i].X;
		if (BitMapVertexPoint[i].Y > max.Y) max.Y = BitMapVertexPoint[i].Y;
	}
	BoundingBox bdbox = { 0, };
	bdbox.LefTop = { min.X,  max.Y };
	bdbox.RightBottom = { max.X, min.Y };
	bdbox.Size = { max.X - min.X, max.Y - min.Y };

	return bdbox;
}

//private :
void GameObject_Sprite::UpdateBitMapVertexPoint() //Angle 값에 따른 꼭짓점 위치 업데이트
{
	if (this->GetHbitmap() == NULL) return;

	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	//현재 클립 상태에 따른 사이즈 조정
	Animation::ClipClass* clip = animation.GetCurrClip();
	CenterPos = Vector2{0,0};
	if (clip != nullptr)
	{
		const Animation::Frame currFrame = animation.GetCurrentFrame();

		bitmap_load.bmWidth = currFrame.Size.cx;
		bitmap_load.bmHeight = currFrame.Size.cy;

		CenterPos.X = (float)currFrame.CenterX * transform.scale.X / 2.f;
		CenterPos.Y = (float)currFrame.CenterY * transform.scale.Y / 2.f;

		if (Flip_X) CenterPos.X *= -1.f;
		if (Flip_Y) CenterPos.Y *= -1.f;
	}

	const int PointSize = 4;
	const float radianAngle = this->GetRadianAngle();
	const float cosRadAngle = (float)cos(radianAngle);
	const float sinRadAngle = (float)sin(radianAngle);
	
	Vector2 DefalutVectexPoint[PointSize] = { 0, };
	DefalutVectexPoint[0] = { -((float)bitmap_load.bmWidth / 2.0f), (float)bitmap_load.bmHeight / 2.0f };
	DefalutVectexPoint[1] = { (float)bitmap_load.bmWidth / 2.0f,  (float)bitmap_load.bmHeight / 2.0f };
	DefalutVectexPoint[2] = { -((float)bitmap_load.bmWidth / 2.0f),  -((float)bitmap_load.bmHeight / 2.0f) };
	DefalutVectexPoint[3] = { ((float)bitmap_load.bmWidth / 2.0f),  -((float)bitmap_load.bmHeight / 2.0f) };
	
	//이미지 반전 여부 확인
	short flip_X = (Flip_X == true) ? -1 : 1;
	short flip_Y = (Flip_Y == true) ? -1 : 1;

	//회전
	if (CenterPos != Vector2{ 0, 0 })
	{
		CenterPos = { (CenterPos.X * cosRadAngle + CenterPos.Y * sinRadAngle), (CenterPos.Y * cosRadAngle - CenterPos.X * sinRadAngle) };
	}
 	Vector2 DirectionVec[PointSize] = { 0, };
	for (int i = 0; i < PointSize; i++)
	{
		DirectionVec[i] = DefalutVectexPoint[i].Normalized();

		//이미지 반전 적용
		DirectionVec[i].X *= flip_X; 
		DirectionVec[i].Y *= flip_Y; 
	}
	float Distance[PointSize] = { 0, };
	for (int i = 0; i < PointSize; i++)
	{
		Distance[i] = DefalutVectexPoint[i].Magnitude();
	}
	Vector2 RotatedDirvec[PointSize] = { 0, };
	for (int i = 0; i < PointSize; i++)
	{
		RotatedDirvec[i] = {
			(DirectionVec[i].X * cosRadAngle - DirectionVec[i].Y * sinRadAngle),
			(DirectionVec[i].Y * cosRadAngle + DirectionVec[i].X * sinRadAngle)
		};
	}
	for (int i = 0; i < PointSize; i++)
	{
		BitMapVertexPoint[i] = RotatedDirvec[i] * Distance[i];
	}
	//크기 증가
	if (GetEnableFlag(FlagTable::ReSize))
	{
		//배율 계산
		float scaleX = (float)this->reSizeWidth / (float)bitmap_load.bmWidth;
		float scaleY = (float)this->reSizeHeight / (float)bitmap_load.bmHeight;
		for (int i = 0; i < PointSize; i++)
		{
			BitMapVertexPoint[i].X *= scaleX;
			BitMapVertexPoint[i].Y *= scaleY;

			bitmap_load.bmWidth *= (LONG)scaleX;
			bitmap_load.bmHeight *= (LONG)scaleY;
		}
	}
	else
	{
		for (int i = 0; i < PointSize; i++)
		{
			BitMapVertexPoint[i].X *= this->transform.scale.X;
			BitMapVertexPoint[i].Y *= this->transform.scale.Y;

			bitmap_load.bmWidth *= (LONG)this->transform.scale.X;
			bitmap_load.bmHeight *= (LONG)this->transform.scale.Y;
		}
	}

	//좌표 이동
	Vector2 Pos = { this->transform.position.X - CenterPos.X, this->transform.position.Y + CenterPos.Y };
	for (int i = 0; i < PointSize; i++)
	{
		BitMapVertexPoint[i] = { BitMapVertexPoint[i].X + Pos.X,  BitMapVertexPoint[i].Y + Pos.Y};
	}

}

POINT GameObject_Sprite::GetBoundingBoxLeftTop(POINT* bitmapPoints)
{
	const int pointSize = 4;

	//포인트 위치에 따른 bounding box 크기 계산
	POINT min = { LONG_MAX, LONG_MAX };
	POINT max = { LONG_MIN, LONG_MIN };
	for (int i = 0; i < pointSize; i++)
	{
		if (bitmapPoints[i].x < min.x) min.x = bitmapPoints[i].x;
		if (bitmapPoints[i].y < min.y) min.y = bitmapPoints[i].y;

		if (bitmapPoints[i].x > max.x) max.x = bitmapPoints[i].x;
		if (bitmapPoints[i].y > max.y) max.y = bitmapPoints[i].y;
	}

	POINT LeftTop = { min.x,  max.y };
	return LeftTop;
}

POINT GameObject_Sprite::GetBoundingBoxSize(POINT* bitmapPoints)
{
	const int pointSize = 4;

	//포인트 위치에 따른 bounding box 크기 계산
	POINT min = { LONG_MAX, LONG_MAX };
	POINT max = { LONG_MIN, LONG_MIN };
	for (int i = 0; i < pointSize; i++)
	{
		if (bitmapPoints[i].x < min.x) min.x = bitmapPoints[i].x;
		if (bitmapPoints[i].y < min.y) min.y = bitmapPoints[i].y;

		if (bitmapPoints[i].x > max.x) max.x = bitmapPoints[i].x;
		if (bitmapPoints[i].y > max.y) max.y = bitmapPoints[i].y;
	}
	POINT boundingBoxSize = { max.x - min.x , max.y - min.y };
	return boundingBoxSize;
}

void GameObject_Sprite::DrawBitmap()
{	
	UpdateBitMapVertexPoint();

	HDC HDC_bitmap = CreateCompatibleDC(backMemDC); //비트맵 불러올 HDC
	SelectObject(HDC_bitmap, this->GetHbitmap()); //해당 비트맵을 그린다
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	HDC HDC_temp = CreateCompatibleDC(backMemDC); //임시 HDC
	HBITMAP HBITMAP_temp = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());	//임시 Hbitmap
	SelectObject(HDC_temp, HBITMAP_temp);

	Animation::ClipClass* clip = animation.GetCurrClip();
	if (clip == nullptr) //애니메이션 클립 활성화 됬는지 확인
	{
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, HDC_bitmap, 0, 0, SRCCOPY); //원본 그대로 복사.
	}
	else
	{
		Animation::Frame currentFrame = animation.GetCurrentFrame();

		//너비, 높이 변경
		bitmap_load.bmWidth = currentFrame.Size.cx;
		bitmap_load.bmHeight = currentFrame.Size.cy;

		//애니메이션 클립 정보에 따라 복사.
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight,
			HDC_bitmap, currentFrame.Source.left, currentFrame.Source.top, SRCCOPY);
	}

	//꼭짓점 좌표 형변환
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = LONG(BitMapVertexPoint[i].X);
		vertexPoint[i].y = LONG(BitMapVertexPoint[i].Y);

		PositionToScreenPos(vertexPoint[i]); //화면 좌표료 변환
	}

	//회전해서 출력
	PlgBlt(backMemDC, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);
	
	//사용한 핸들 삭제
	DeleteDC(HDC_temp);
	DeleteObject(HBITMAP_temp);

	DeleteDC(HDC_bitmap);
}

void GameObject_Sprite::DrawBitmap_TransparentBlt()
{
	UpdateBitMapVertexPoint();

	HDC HDC_bitmap = CreateCompatibleDC(backMemDC); //비트맵 불러올 HDC
	SelectObject(HDC_bitmap, this->GetHbitmap()); //해당 비트맵을 그린다
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	HDC HDC_temp = CreateCompatibleDC(backMemDC); //임시 HDC
	HBITMAP HBITMAP_temp = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());	//임시 Hbitmap
	SelectObject(HDC_temp, HBITMAP_temp);

	Animation::ClipClass* clip = animation.GetCurrClip();
	if (clip == nullptr) //애니메이션 클립 활성화 됬는지 확인
	{
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, HDC_bitmap, 0, 0, SRCCOPY); //원본 그대로 복사.
	}
	else
	{
		const Animation::Frame currentFrame = animation.GetCurrentFrame();

		//너비, 높이 변경
		bitmap_load.bmWidth = currentFrame.Size.cx;
		bitmap_load.bmHeight = currentFrame.Size.cy;

		//애니메이션 클립 정보에 따라 복사.
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight,
			HDC_bitmap, currentFrame.Source.left, currentFrame.Source.top, SRCCOPY);
	}

	//형변환
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = (LONG)BitMapVertexPoint[i].X;
		vertexPoint[i].y = (LONG)BitMapVertexPoint[i].Y;	
	}
	//왼쪽 상단으로 맞춘다.
	POINT ZeroPoint = GetBoundingBoxLeftTop(vertexPoint);
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x -= ZeroPoint.x;
		vertexPoint[i].y -= ZeroPoint.y;
		vertexPoint[i].y += WinApp::GetWinApp().GetClientHeight();
		PositionToScreenPos(vertexPoint[i]); //화면 좌표료 변환
	}

	//비트맵을 그린다
	SelectObject(HDC_temp, this->GetHbitmap());

	//회전한 물체 임시로 HDC에 그린다
	HDC HDC_rotation = CreateCompatibleDC(backMemDC); 
	HBITMAP HBITMAP_rotation = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_rotation, HBITMAP_rotation);
	DrawRect(HDC_rotation, { 0, 0 }, { (short)WinApp::GetWinApp().GetClientWidth(), (short)WinApp::GetWinApp().GetClientHeight() }, GetTrColor());
	PlgBlt(HDC_rotation, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);

	//오브젝트 위치에 따른 출력 위치
	POINT boundingBoxSize = GetBoundingBoxSize(vertexPoint); //바운딩 박스 크기 계산
	COORD outPos = { short( this->transform.position.X - CenterPos.X ), short(this->transform.position.Y + CenterPos.Y) };
	PositionToScreenPos(outPos);
	outPos.X -= short(boundingBoxSize.x / 2.0);
	outPos.Y -= short(boundingBoxSize.y / 2.0);

	//배경 지워서 버퍼에 출력
	TransparentBlt(
		backMemDC, outPos.X, outPos.Y, boundingBoxSize.x, boundingBoxSize.y,
		HDC_rotation, 0, 0, boundingBoxSize.x, boundingBoxSize.y, GetTrColor()
	);
	
	//사용한 핸들, Object 삭제
	DeleteDC(HDC_temp);
	DeleteObject(HBITMAP_temp);

	DeleteDC(HDC_rotation);
	DeleteObject(HBITMAP_rotation);

	DeleteDC(HDC_bitmap);	
}

void GameObject_Sprite::DrawBitmap_AlphaBlend()
{
	UpdateBitMapVertexPoint();

	HDC HDC_bitmap = CreateCompatibleDC(backMemDC); //비트맵 불러올 HDC
	SelectObject(HDC_bitmap, this->GetHbitmap()); //해당 비트맵을 그린다
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	HDC HDC_temp = CreateCompatibleDC(backMemDC); //임시 HDC
	HBITMAP HBITMAP_temp = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());	//임시 Hbitmap
	SelectObject(HDC_temp, HBITMAP_temp);

	Animation::ClipClass* clip = animation.GetCurrClip();
	if (clip == nullptr) //애니메이션 클립 활성화 됬는지 확인
	{
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, HDC_bitmap, 0, 0, SRCCOPY); //원본 그대로 복사.
	}
	else
	{
		const Animation::Frame currentFrame = animation.GetCurrentFrame();

		//너비, 높이 변경
		bitmap_load.bmWidth = currentFrame.Size.cx;
		bitmap_load.bmHeight = currentFrame.Size.cy;

		//애니메이션 클립 정보에 따라 복사.
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight,
			HDC_bitmap, currentFrame.Source.left, currentFrame.Source.top, SRCCOPY);
	}

	//형변환
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = (LONG)BitMapVertexPoint[i].X;
		vertexPoint[i].y = (LONG)BitMapVertexPoint[i].Y;
	}
	//왼쪽 상단으로 맞춘다.
	POINT ZeroPoint = GetBoundingBoxLeftTop(vertexPoint);
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x -= ZeroPoint.x;
		vertexPoint[i].y -= ZeroPoint.y;
		vertexPoint[i].y += WinApp::GetWinApp().GetClientHeight();
		PositionToScreenPos(vertexPoint[i]); //화면 좌표료 변환
	}

	//비트맵을 그린다
	SelectObject(HDC_temp, this->GetHbitmap());

	//회전한 물체 임시로 HDC에 그린다
	HDC HDC_rotation = CreateCompatibleDC(backMemDC);
	HBITMAP HBITMAP_rotation = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_rotation, HBITMAP_rotation);
	DrawRect(HDC_rotation, { 0, 0 }, { (short)WinApp::GetWinApp().GetClientWidth(), (short)WinApp::GetWinApp().GetClientHeight() }, GetTrColor());	
	PlgBlt(HDC_rotation, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);

	//오브젝트 위치에 따른 출력 위치
	POINT boundingBoxSize = GetBoundingBoxSize(vertexPoint); //바운딩 박스 크기 계산
	COORD outPos = { short(this->transform.position.X - CenterPos.X), short(this->transform.position.Y + CenterPos.Y) };
	PositionToScreenPos(outPos);
	outPos.X -= short(boundingBoxSize.x / 2.0);
	outPos.Y -= short(boundingBoxSize.y / 2.0);
	//알파값 적용 후 버퍼에 출력
	// BLENDFUNCTION 구조체
	BLENDFUNCTION bf = { 0, };
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = int(255 * GetAlpha()); // 투명도(투명 0 - 불투명 255)
	AlphaBlend(
		backMemDC, outPos.X, outPos.Y, boundingBoxSize.x, boundingBoxSize.y,
		HDC_rotation, 0, 0, boundingBoxSize.x, boundingBoxSize.y, bf
	);

	//사용한 핸들, Object 삭제
	DeleteDC(HDC_temp);
	DeleteObject(HBITMAP_temp);

	DeleteDC(HDC_rotation);
	DeleteObject(HBITMAP_rotation);

	DeleteDC(HDC_bitmap);
}

void GameObject_Sprite::DrawBitmap_AlphaAndTransparent()
{
	UpdateBitMapVertexPoint();

	HDC HDC_bitmap = CreateCompatibleDC(backMemDC); //비트맵 불러올 HDC
	SelectObject(HDC_bitmap, this->GetHbitmap()); //해당 비트맵을 그린다
	BITMAP bitmap_load = { 0 }; //불러온 비트맵 정보 담을 구조체
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //불러온 비트맵의 정보를 담는다

	HDC HDC_temp = CreateCompatibleDC(backMemDC); //임시 HDC
	HBITMAP HBITMAP_temp = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());	//임시 Hbitmap
	SelectObject(HDC_temp, HBITMAP_temp);

	Animation::ClipClass* clip = animation.GetCurrClip();
	if (clip == nullptr) //애니메이션 클립 활성화 됬는지 확인
	{
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, HDC_bitmap, 0, 0, SRCCOPY); //원본 그대로 복사.
	}
	else
	{
		const Animation::Frame currentFrame = animation.GetCurrentFrame();

		//너비, 높이 변경
		bitmap_load.bmWidth = currentFrame.Size.cx;
		bitmap_load.bmHeight = currentFrame.Size.cy;

		//애니메이션 클립 정보에 따라 복사.
		BitBlt(HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight,
			HDC_bitmap, currentFrame.Source.left, currentFrame.Source.top, SRCCOPY);
	}

	//형변환
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = (LONG)BitMapVertexPoint[i].X;
		vertexPoint[i].y = (LONG)BitMapVertexPoint[i].Y;
	}
	//왼쪽 상단으로 맞춘다.
	POINT ZeroPoint = GetBoundingBoxLeftTop(vertexPoint);
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x -= ZeroPoint.x;
		vertexPoint[i].y -= ZeroPoint.y;
		vertexPoint[i].y += WinApp::GetWinApp().GetClientHeight();
		PositionToScreenPos(vertexPoint[i]); //화면 좌표료 변환
	}

	//비트맵을 그린다
	SelectObject(HDC_temp, this->GetHbitmap());

	//회전한 물체 임시로 HDC에 그린다	
	HDC HDC_rotation = CreateCompatibleDC(backMemDC);
	HBITMAP HBITMAP_rotation = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_rotation, HBITMAP_rotation);
	DrawRect(HDC_rotation, { 0, 0 }, { (short)WinApp::GetWinApp().GetClientWidth(), (short)WinApp::GetWinApp().GetClientHeight() }, GetTrColor());
	PlgBlt(HDC_rotation, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);

	//오브젝트 위치에 따른 출력 위치
	POINT boundingBoxSize = GetBoundingBoxSize(vertexPoint); //바운딩 박스 크기 계산
	COORD outPos = { short(this->transform.position.X - CenterPos.X), short(this->transform.position.Y + CenterPos.Y) };
	PositionToScreenPos(outPos);
	outPos.X -= short(boundingBoxSize.x / 2.0);
	outPos.Y -= short(boundingBoxSize.y / 2.0);
	//배경 제거
	HDC HDC_Alpha = CreateCompatibleDC(backMemDC);
	HBITMAP HBITMAP_Alpha = CreateCompatibleBitmap(frontMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_Alpha, HBITMAP_Alpha);
	BitBlt(
		HDC_Alpha, 0, 0, boundingBoxSize.x, boundingBoxSize.y, 
		backMemDC, outPos.X, outPos.Y, SRCCOPY); //출력할 위치의 backMemdc를 alpha용 MemDc에 복사한다.
	TransparentBlt(
		HDC_Alpha, 0, 0, boundingBoxSize.x, boundingBoxSize.y,
		HDC_rotation, 0, 0, boundingBoxSize.x, boundingBoxSize.y, GetTrColor()); //배경 지워서 alpha용 DC에 합친다.

	//Alpha값 적용후 backMemDC에 출력
	// BLENDFUNCTION 구조체
	BLENDFUNCTION bf = { 0, };
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = int(255 * GetAlpha()); // 투명도(투명 0 - 불투명 255)
	AlphaBlend(
		backMemDC, outPos.X, outPos.Y, boundingBoxSize.x, boundingBoxSize.y,
		HDC_Alpha, 0, 0, boundingBoxSize.x, boundingBoxSize.y, bf
	);

	//사용한 핸들, Object 삭제
	DeleteDC(HDC_temp);
	DeleteObject(HBITMAP_temp);

	DeleteDC(HDC_rotation);
	DeleteObject(HBITMAP_rotation);

	DeleteDC(HDC_Alpha);
	DeleteObject(HBITMAP_Alpha);

	DeleteDC(HDC_bitmap);
}

bool GameObject_Sprite::isCollisionAABB(const BoundingBox& B)
{
	return Collision::CheckCollisionAABB(this->GetBounds(), B);
}

bool GameObject_Sprite::isCollisionAABB(const Vector2& B)
{
	return Collision::CheckCollisionAABB(this->GetBounds(), B);
}

