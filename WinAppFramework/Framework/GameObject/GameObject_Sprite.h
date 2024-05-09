#pragma once
#include "..\GameObjectBase.h"

class GameObject_Sprite : public GameObjectBase, public Render
{

public:
	enum class FlagTable
	{
		ReScale = 0b1000,
		ReSize = 0b0100,
		Alpha = 0b0010,
		Transparent = 0b0001
	};
	GameObject_Sprite();
	virtual ~GameObject_Sprite();
	GameObject_Sprite& operator=(const GameObject_Sprite&);

	Animation animation;

	bool Flip_X = false;
	bool Flip_Y = false;

	virtual void Rendering() override;

	void SetAngle(float angle);
	float GetAngle() const { return angle; }

	float GetRadianAngle();
	Vector2 GetDir();

	void Loadbmp(const char* path);

	HBITMAP GetHbitmap();
	void ReleasebitMap();

	void SetReSize(int ReSizeWidth, int ReSizeHeight);
	COORD GetReSize();

	void SetAlpha(float alpha);
	float GetAlpha();

	void SetTrColor(COLORREF RGB);
	COLORREF GetTrColor();

	void SetEnableFlag(FlagTable flag, bool isEnable);
	bool GetEnableFlag(FlagTable flag);

	BoundingBox GetBounds();

	bool isCollisionAABB(const BoundingBox& B);
	bool isCollisionAABB(const Vector2& B);

private:
	HBITMAP Hbitmap;

	float angle;

	int reSizeWidth;
	int reSizeHeight;

	float Alpha;

	COLORREF crTransparent;

	unsigned short bitflag;

	Vector2 BitMapVertexPoint[4];
	Vector2 CenterPos = { 0,0 };

	void UpdateBitMapVertexPoint();
	POINT GetBoundingBoxLeftTop(POINT* bitmapPoints);
	POINT GetBoundingBoxSize(POINT* bitmapPoints);

	void DrawBitmap();
	void DrawBitmap_TransparentBlt();
	void DrawBitmap_AlphaBlend();
	void DrawBitmap_AlphaAndTransparent();
};