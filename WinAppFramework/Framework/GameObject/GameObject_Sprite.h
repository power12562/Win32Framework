#pragma once
#include "..\GameObjectBase.h"

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
	class Animation_Sprite : public Animation
	{
	public:
		void InitGameObject(GameObject_Sprite* _gameObject)
		{
			if (gameObject == nullptr) gameObject = _gameObject;
			else throw; //포인터 변경 불가능
		}
		virtual void UpdateFrmae(float DeltaTime) override
		{
			if (CurrentClip == nullptr) return;

			elapsedTime += DeltaTime;
			while (elapsedTime >= CurrentClip->frameIntervalTime) //시간 도달하면 다음 프레임으로 변경
			{
				CurrentFrame++;
				elapsedTime -= CurrentClip->frameIntervalTime;

				if (CurrentFrame < CurrentClip->FrameCount)
					gameObject->UpdateBitMapVertexPoint();
			}
			if (CurrentFrame == CurrentClip->FrameCount) //애니메이션 종료시
			{
				if (CurrentClip->IsLoop == true) //루프 확인
					CurrentFrame = 0; //루프
				else
				{
					CurrentFrame--;
					isCurrentClipEnd = true;
				}
			}
		}
	private:
		GameObject_Sprite* gameObject = nullptr;
	};
	struct Transform
	{
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
	virtual ~GameObject_Sprite();
	GameObject_Sprite& operator=(const GameObject_Sprite&);

	Animation_Sprite animation;

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