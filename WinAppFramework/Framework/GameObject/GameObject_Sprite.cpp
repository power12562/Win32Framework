#include "GameObject.h"
#include "..\WinApp.h"
#include <math.h>
#include <float.h>
#include "..\DataType\Collision.h"
#include "..\DataType\Mathf.h"

GameObject_Sprite::GameObject_Sprite()
{
	transform.position.InitGameObject(this);
	transform.scale.InitGameObject(this);

	this->Hbitmap = NULL;
	
	this->angle = 0;
	for (int i = 0; i < 4; i++)
	{
		this->BitMapVertexPoint[i] = Vector2{0, 0};
	}
	this->SetAngle(angle);

	this->transform.scale = { 1.0f, 1.0f };

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

//position ������ �����ε�:
Vector2& GameObject_Sprite::Position::operator=(const Vector2 other)
{
	this->X = other.X;
	this->Y = other.Y;

	this->gameObject->PosToRotationPos();

	return *this;
}
Vector2& GameObject_Sprite::Position::operator+=(const Vector2& other)
{
	this->X += other.X;
	this->Y += other.Y;

	this->gameObject->PosToRotationPos();

	return *this;
}
Vector2& GameObject_Sprite::Position::operator-=(const Vector2& other)
{
	this->X -= other.X;
	this->Y -= other.Y;

	this->gameObject->PosToRotationPos();

	return *this;
}

//scale ������ �����ε�:
Vector2& GameObject_Sprite::Scale::operator=(const Vector2 other)
{
	this->X = other.X;
	this->Y = other.X;

	gameObject->SetEnableFlag(FlagTable::ReScale, true);

	gameObject->PosToRotationPos();

	return *this;
}
Vector2& GameObject_Sprite::Scale::operator=(const float scala)
{
	this->X = scala;
	this->Y = scala;

	gameObject->SetEnableFlag(FlagTable::ReScale, true);

	gameObject->PosToRotationPos();

	return *this;
}

Vector2& GameObject_Sprite::Scale::operator+=(const Vector2& other)
{
	this->X += other.X;
	this->Y += other.X;

	gameObject->SetEnableFlag(FlagTable::ReScale, true);

	gameObject->PosToRotationPos();

	return *this;
}

Vector2& GameObject_Sprite::Scale::operator-=(const Vector2& other)
{
	this->X -= other.X;
	this->Y -= other.X;

	gameObject->SetEnableFlag(FlagTable::ReScale, true);

	gameObject->PosToRotationPos();

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

void GameObject_Sprite::SetPos(Vector2 pos)
{
	transform.position = pos;	
}

void GameObject_Sprite::SetAngle(float angle)
{
	this->angle = angle;

	//��Ʈ�� ������ ȸ��
	PosToRotationPos();
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
		DeleteObject(Hbitmap); //���� �ִ� ��Ʈ���� ����
	}
	this->Hbitmap = (HBITMAP)LoadImageA(
		hInstance, path, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

	PosToRotationPos();
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
		DeleteObject(Hbitmap); //���� �ִ� ��Ʈ���� ����
	}
	this->Hbitmap = NULL;	
}

void GameObject_Sprite::SetScale(Vector2 scale)
{
	this->transform.scale.X = scale.X;
	this->transform.scale.Y = scale.X;

	this->SetEnableFlag(FlagTable::ReScale, true);

	this->PosToRotationPos();
}
void GameObject_Sprite::SetScale(float scaleXY)
{
	this->transform.scale.X = scaleXY;
	this->transform.scale.Y = scaleXY;

	this->SetEnableFlag(FlagTable::ReScale, true);

	this->PosToRotationPos();
}
Vector2 GameObject_Sprite::GetScale()
{
	return this->transform.scale;
}

void GameObject_Sprite::SetReSize(int ReSizeWidth, int ReSizeHeight)
{
	this->reSizeWidth = ReSizeWidth;
	this->reSizeHeight = ReSizeHeight;
	this->SetEnableFlag(FlagTable::ReSize, true);

	this->PosToRotationPos();
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

BoundingBox GameObject_Sprite::GetBounds() const
{
	const int pointSize = 4;

	//����Ʈ ��ġ�� ���� bounding box ũ�� ���
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
void GameObject_Sprite::PosToRotationPos()
{
	if (this->GetHbitmap() == NULL) return;

	BITMAP bitmap_load = { 0 }; //�ҷ��� ��Ʈ�� ���� ���� ����ü
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //�ҷ��� ��Ʈ���� ������ ��´�

	const int PointSize = 4;
	const float radianAngle = this->GetRadianAngle();
	const float cosRadAngle = (float)cos(radianAngle);
	const float sinRadAngle = (float)sin(radianAngle);

	Vector2 DefalutVectexPoint[PointSize] = { 0, };
	DefalutVectexPoint[0] = { -((float)bitmap_load.bmWidth / 2.0f), (float)bitmap_load.bmHeight / 2.0f };
	DefalutVectexPoint[1] = { (float)bitmap_load.bmWidth / 2.0f,  (float)bitmap_load.bmHeight / 2.0f };
	DefalutVectexPoint[2] = { -((float)bitmap_load.bmWidth / 2.0f),  -((float)bitmap_load.bmHeight / 2.0f) };
	DefalutVectexPoint[3] = { ((float)bitmap_load.bmWidth / 2.0f),  -((float)bitmap_load.bmHeight / 2.0f) };

	//ȸ��
	Vector2 DirectionVec[PointSize] = { 0, };
	for (int i = 0; i < PointSize; i++)
	{
		DirectionVec[i] = DefalutVectexPoint[i].Normalized();
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
			(DirectionVec[i].X * cosRadAngle) - (DirectionVec[i].Y * sinRadAngle),
			(DirectionVec[i].Y * cosRadAngle) + (DirectionVec[i].X * sinRadAngle)
		};
	}
	for (int i = 0; i < PointSize; i++)
	{
		BitMapVertexPoint[i] = RotatedDirvec[i] * Distance[i];
	}
	//ũ�� ����
	if (GetEnableFlag(FlagTable::ReSize))
	{
		//���� ���
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
	else if (GetEnableFlag(FlagTable::ReScale))
	{
		for (int i = 0; i < PointSize; i++)
		{
			BitMapVertexPoint[i].X *= this->transform.scale.X;
			BitMapVertexPoint[i].Y *= this->transform.scale.Y;

			bitmap_load.bmWidth *= (LONG)this->transform.scale.X;
			bitmap_load.bmHeight *= (LONG)this->transform.scale.Y;
		}
	}

	//��ǥ �̵�
	Vector2 Pos = { this->transform.position.X, this->transform.position.Y };
	for (int i = 0; i < PointSize; i++)
	{
		BitMapVertexPoint[i] = { BitMapVertexPoint[i].X + Pos.X,  BitMapVertexPoint[i].Y + Pos.Y };
	}

}

POINT GameObject_Sprite::GetBoundingBoxLeftTop(POINT* bitmapPoints)
{
	const int pointSize = 4;

	//����Ʈ ��ġ�� ���� bounding box ũ�� ���
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

	//����Ʈ ��ġ�� ���� bounding box ũ�� ���
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
	HDC HDC_temp = CreateCompatibleDC(backMemDC);
	BITMAP bitmap_load = { 0 }; //�ҷ��� ��Ʈ�� ���� ���� ����ü
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //�ҷ��� ��Ʈ���� ������ ��´�

	//����ȯ
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = (LONG)BitMapVertexPoint[i].X;
		vertexPoint[i].y = (LONG)BitMapVertexPoint[i].Y;	

		PositionToScreenPos(vertexPoint[i]); //ȭ�� ��ǥ�� ��ȯ
	}

	//�ش� ��Ʈ���� �׸���
	SelectObject(HDC_temp, this->GetHbitmap());

	//ȸ���ؼ� ���
	PlgBlt(backMemDC, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);
	
	//����� �ڵ� ����
	DeleteDC(HDC_temp);
}

void GameObject_Sprite::DrawBitmap_TransparentBlt()
{
	HDC HDC_temp = CreateCompatibleDC(backMemDC); //��Ʈ�� �׸� HDC
	BITMAP bitmap_load = { 0 }; //�ҷ��� ��Ʈ�� ���� ���� ����ü
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //�ҷ��� ��Ʈ���� ������ ��´�

	//����ȯ
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = (LONG)BitMapVertexPoint[i].X;
		vertexPoint[i].y = (LONG)BitMapVertexPoint[i].Y;	
	}
	//���� ������� �����.
	POINT ZeroPoint = GetBoundingBoxLeftTop(vertexPoint);
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x -= ZeroPoint.x;
		vertexPoint[i].y -= ZeroPoint.y;
		vertexPoint[i].y += WinApp::GetWinApp().GetClientHeight();
		PositionToScreenPos(vertexPoint[i]); //ȭ�� ��ǥ�� ��ȯ
	}

	//��Ʈ���� �׸���
	SelectObject(HDC_temp, this->GetHbitmap());

	//ȸ���� ��ü �ӽ÷� HDC�� �׸���
	HDC HDC_rotation = CreateCompatibleDC(backMemDC); 
	HBITMAP HBITMAP_rotation = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_rotation, HBITMAP_rotation);
	DrawRect(HDC_rotation, { 0, 0 }, { (short)WinApp::GetWinApp().GetClientWidth(), (short)WinApp::GetWinApp().GetClientHeight() }, GetTrColor());
	PlgBlt(HDC_rotation, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);

	//������Ʈ ��ġ�� ���� ��� ��ġ
	POINT boundingBoxSize = GetBoundingBoxSize(vertexPoint); //�ٿ�� �ڽ� ũ�� ���
	COORD outPos = { (short)this->transform.position.X, (short)this->transform.position.Y };
	PositionToScreenPos(outPos);
	outPos.X -= short(boundingBoxSize.x / 2.0);
	outPos.Y -= short(boundingBoxSize.y / 2.0);

	//��� ������ ���ۿ� ���
	TransparentBlt(
		backMemDC, outPos.X, outPos.Y, boundingBoxSize.x, boundingBoxSize.y,
		HDC_rotation, 0, 0, boundingBoxSize.x, boundingBoxSize.y, GetTrColor()
	);
	
	//����� �ڵ�, Object ����
	DeleteDC(HDC_temp);
	DeleteDC(HDC_rotation);
	DeleteObject(HBITMAP_rotation);
}

void GameObject_Sprite::DrawBitmap_AlphaBlend()
{
	HDC HDC_temp = CreateCompatibleDC(backMemDC); //��Ʈ�� �׸� HDC
	BITMAP bitmap_load = { 0 }; //�ҷ��� ��Ʈ�� ���� ���� ����ü
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //�ҷ��� ��Ʈ���� ������ ��´�

	//����ȯ
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = (LONG)BitMapVertexPoint[i].X;
		vertexPoint[i].y = (LONG)BitMapVertexPoint[i].Y;
	}
	//���� ������� �����.
	POINT ZeroPoint = GetBoundingBoxLeftTop(vertexPoint);
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x -= ZeroPoint.x;
		vertexPoint[i].y -= ZeroPoint.y;
		vertexPoint[i].y += WinApp::GetWinApp().GetClientHeight();
		PositionToScreenPos(vertexPoint[i]); //ȭ�� ��ǥ�� ��ȯ
	}

	//��Ʈ���� �׸���
	SelectObject(HDC_temp, this->GetHbitmap());

	//ȸ���� ��ü �ӽ÷� HDC�� �׸���
	HDC HDC_rotation = CreateCompatibleDC(backMemDC);
	HBITMAP HBITMAP_rotation = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_rotation, HBITMAP_rotation);
	DrawRect(HDC_rotation, { 0, 0 }, { (short)WinApp::GetWinApp().GetClientWidth(), (short)WinApp::GetWinApp().GetClientHeight() }, GetTrColor());	
	PlgBlt(HDC_rotation, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);

	//������Ʈ ��ġ�� ���� ��� ��ġ
	POINT boundingBoxSize = GetBoundingBoxSize(vertexPoint); //�ٿ�� �ڽ� ũ�� ���
	COORD outPos = { (short)this->transform.position.X, (short)this->transform.position.Y };
	PositionToScreenPos(outPos);
	outPos.X -= short(boundingBoxSize.x / 2.0);
	outPos.Y -= short(boundingBoxSize.y / 2.0);
	//���İ� ���� �� ���ۿ� ���
	// BLENDFUNCTION ����ü
	BLENDFUNCTION bf = { 0, };
	bf.AlphaFormat = 0; // ��Ʈ�� ������ �Ϲ� ��Ʈ���� ��� 0, 32��Ʈ ��Ʈ���� ��� AC_SRC_ALPHA
	bf.BlendFlags = 0; // ������ 0�̾�� �Ѵ�
	bf.BlendOp = AC_SRC_OVER; // ������ AC_SRC_OVER�̾�� �ϰ� ������ ��� �̹����� ��ģ�ٴ� �ǹ�
	bf.SourceConstantAlpha = int(255 * GetAlpha()); // ������(���� 0 - ������ 255)
	AlphaBlend(
		backMemDC, outPos.X, outPos.Y, boundingBoxSize.x, boundingBoxSize.y,
		HDC_rotation, 0, 0, boundingBoxSize.x, boundingBoxSize.y, bf
	);

	//����� �ڵ�, Object ����
	DeleteDC(HDC_temp);
	DeleteDC(HDC_rotation);
	DeleteObject(HBITMAP_rotation);
}

void GameObject_Sprite::DrawBitmap_AlphaAndTransparent()
{
	HDC HDC_temp = CreateCompatibleDC(backMemDC); //��Ʈ�� �׸� HDC
	BITMAP bitmap_load = { 0 }; //�ҷ��� ��Ʈ�� ���� ���� ����ü
	GetObject(this->GetHbitmap(), sizeof(bitmap_load), &bitmap_load); //�ҷ��� ��Ʈ���� ������ ��´�

	//����ȯ
	const int pointSize = 4;
	POINT vertexPoint[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x = (LONG)BitMapVertexPoint[i].X;
		vertexPoint[i].y = (LONG)BitMapVertexPoint[i].Y;
	}
	//���� ������� �����.
	POINT ZeroPoint = GetBoundingBoxLeftTop(vertexPoint);
	for (int i = 0; i < 4; i++)
	{
		vertexPoint[i].x -= ZeroPoint.x;
		vertexPoint[i].y -= ZeroPoint.y;
		vertexPoint[i].y += WinApp::GetWinApp().GetClientHeight();
		PositionToScreenPos(vertexPoint[i]); //ȭ�� ��ǥ�� ��ȯ
	}

	//��Ʈ���� �׸���
	SelectObject(HDC_temp, this->GetHbitmap());

	//ȸ���� ��ü �ӽ÷� HDC�� �׸���	
	HDC HDC_rotation = CreateCompatibleDC(backMemDC);
	HBITMAP HBITMAP_rotation = CreateCompatibleBitmap(backMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_rotation, HBITMAP_rotation);
	DrawRect(HDC_rotation, { 0, 0 }, { (short)WinApp::GetWinApp().GetClientWidth(), (short)WinApp::GetWinApp().GetClientHeight() }, GetTrColor());
	PlgBlt(HDC_rotation, vertexPoint, HDC_temp, 0, 0, bitmap_load.bmWidth, bitmap_load.bmHeight, NULL, 0, 0);

	//������Ʈ ��ġ�� ���� ��� ��ġ
	POINT boundingBoxSize = GetBoundingBoxSize(vertexPoint); //�ٿ�� �ڽ� ũ�� ���
	COORD outPos = { (short)this->transform.position.X, (short)this->transform.position.Y };
	PositionToScreenPos(outPos);
	outPos.X -= short(boundingBoxSize.x / 2.0);
	outPos.Y -= short(boundingBoxSize.y / 2.0);
	//��� ����
	HDC HDC_Alpha = CreateCompatibleDC(backMemDC);
	HBITMAP HBITMAP_Alpha = CreateCompatibleBitmap(frontMemDC, WinApp::GetWinApp().GetClientWidth(), WinApp::GetWinApp().GetClientHeight());
	SelectObject(HDC_Alpha, HBITMAP_Alpha);
	BitBlt(
		HDC_Alpha, 0, 0, boundingBoxSize.x, boundingBoxSize.y, 
		backMemDC, outPos.X, outPos.Y, SRCCOPY); //����� ��ġ�� backMemdc�� alpha�� MemDc�� �����Ѵ�.
	TransparentBlt(
		HDC_Alpha, 0, 0, boundingBoxSize.x, boundingBoxSize.y,
		HDC_rotation, 0, 0, boundingBoxSize.x, boundingBoxSize.y, GetTrColor()); //��� ������ alpha�� DC�� ��ģ��.

	//Alpha�� ������ backMemDC�� ���
	// BLENDFUNCTION ����ü
	BLENDFUNCTION bf = { 0, };
	bf.AlphaFormat = 0; // ��Ʈ�� ������ �Ϲ� ��Ʈ���� ��� 0, 32��Ʈ ��Ʈ���� ��� AC_SRC_ALPHA
	bf.BlendFlags = 0; // ������ 0�̾�� �Ѵ�
	bf.BlendOp = AC_SRC_OVER; // ������ AC_SRC_OVER�̾�� �ϰ� ������ ��� �̹����� ��ģ�ٴ� �ǹ�
	bf.SourceConstantAlpha = int(255 * GetAlpha()); // ������(���� 0 - ������ 255)
	AlphaBlend(
		backMemDC, outPos.X, outPos.Y, boundingBoxSize.x, boundingBoxSize.y,
		HDC_Alpha, 0, 0, boundingBoxSize.x, boundingBoxSize.y, bf
	);

	//����� �ڵ�, Object ����
	DeleteDC(HDC_temp);
	DeleteDC(HDC_rotation);
	DeleteObject(HBITMAP_rotation);
	DeleteDC(HDC_Alpha);
	DeleteObject(HBITMAP_Alpha);
}

bool GameObject_Sprite::isCollisionAABB(const BoundingBox& B) const
{
	return Collision::CheckCollisionAABB(this->GetBounds(), B);
}

bool GameObject_Sprite::isCollisionAABB(const Vector2& B) const
{
	return Collision::CheckCollisionAABB(this->GetBounds(), B);
}
