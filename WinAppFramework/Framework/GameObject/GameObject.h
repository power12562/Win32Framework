#pragma once
#include "..\RenderSystem.h"
#include "..\DataType\Vector2.h"
#include "..\DataType\wString.h"

class GameObjectBase
{
	struct Transform
	{
		Vector2 position;
		Vector2 scale;
	};
public:

	GameObjectBase() = default;
	~GameObjectBase() = default;

	Transform transform;

private:

};

class GameObject_Line : public GameObjectBase, public Render
{
public:
	GameObject_Line();
	~GameObject_Line();

	void Rendering();
	void SetOriginToStartVertex(Vector2 position);
	void SetOriginToEndVertex(Vector2 position);
	void SetColor(COLORREF RGB);
	void SetLineWidth(int Width);

private:
	Vector2 originToStartVertex;
	Vector2 originToEndVertex;
	COLORREF color;
	int LineWidth;
};

class GameObject_Square : public GameObjectBase, public Render
{
public:
	GameObject_Square();
	~GameObject_Square();

	void SetOriginToLeftTop(Vector2 position);
	void SetOriginToRightBottom(Vector2 position);
	void SetSquareSize(int width, int height);
	void SetColor(COLORREF RGB);
	void Rendering();
	BoundingBox GetBounds();

private:
	Vector2 originToLeftTop;
	Vector2 originToRightBottom;
	COLORREF color;
};

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

class GameObject_Polygon : public GameObjectBase, public Render
{
public:
	GameObject_Polygon();
	~GameObject_Polygon();

	void Rendering();
	void SetOriginToPoints(POINT points[], int vertextCount);
	void SetColor(COLORREF RGB);

private:
	int vertexCount;
	POINT* originToPoint;
	COLORREF color;
};

class GameObject_Text : public GameObjectBase, public Render
{
public:
	GameObject_Text();
	~GameObject_Text();

	void Rendering();
	void SetText(const char* string, int stringLen);
	void SetColor(COLORREF RGB);

private:
	char* text;
	COLORREF color;
};

class GameObject_Sprite : public Render
{
	class Position : public Vector2 
	{
	public:
		Vector2& operator=(const Vector2 other);
		virtual Vector2& operator+=(const Vector2& other) override;
		virtual Vector2& operator-=(const Vector2& other) override;

		void InitGameObject(GameObject_Sprite* _gameObject) 
		{ 
			if (gameObject == nullptr) gameObject = _gameObject;
			else throw; //포인터 변경 불가능
		}
	private:
		GameObject_Sprite* gameObject = nullptr;
	};
	class Scale : public Vector2
	{
	public:
		Vector2& operator=(const Vector2 other);
		Vector2& operator=(const float scala);
		virtual Vector2& operator+=(const Vector2& other) override;
		virtual Vector2& operator-=(const Vector2& other) override;

		void InitGameObject(GameObject_Sprite* _gameObject)
		{
			if (gameObject == nullptr) gameObject = _gameObject;
			else throw; //포인터 변경 불가능
		}
	private:
		GameObject_Sprite* gameObject = nullptr;
	};

	class Transform
	{
	public:
		Position position;
		Scale scale;
	};

public:
	Transform transform;

	enum class FlagTable
	{
		ReScale = 0b1000,
		ReSize = 0b0100,
		Alpha = 0b0010,
		Transparent = 0b0001
	};

	GameObject_Sprite();
	~GameObject_Sprite();
	GameObject_Sprite& operator=(const GameObject_Sprite&); //복사

	void Rendering();

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

	BoundingBox GetBounds() const;

	bool isCollisionAABB(const BoundingBox& B) const;
	bool isCollisionAABB(const Vector2& B) const;

private:
	HBITMAP Hbitmap;

	float angle;

	int reSizeWidth;
	int reSizeHeight;

	float Alpha;

	COLORREF crTransparent;

	unsigned short bitflag;

	Vector2 BitMapVertexPoint[4];

	void PosToRotationPos();
	POINT GetBoundingBoxLeftTop(POINT* bitmapPoints);
	POINT GetBoundingBoxSize(POINT* bitmapPoints);

	void DrawBitmap();
	void DrawBitmap_TransparentBlt();
	void DrawBitmap_AlphaBlend();
	void DrawBitmap_AlphaAndTransparent();
};


class GameObject_Font : public GameObjectBase, public Render
{
public:
	GameObject_Font();
	~GameObject_Font();

	void Rendering();

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

