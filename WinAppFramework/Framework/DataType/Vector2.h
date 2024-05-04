#pragma once

//사용되는 구조체 모음 헤더
class Vector2
{

public:
	float X;
	float Y;

	static Vector2 Right() { return { 1,0 }; }
	static Vector2 Left() { return { -1,0 }; }
	static Vector2 Up() { return { 0,1 }; }
	static Vector2 Down() { return { 0,-1 }; }

	Vector2(float x = 0, float y = 0);
	Vector2(double x, double y);
	Vector2(int x, int y);
	~Vector2() = default;

	Vector2(const Vector2& other);

	float Magnitude();

	Vector2 Normalized();

	static Vector2 Lerp(Vector2 startPos, Vector2 EndPos, float t); //선형 보간

	virtual Vector2 operator*(const float scala) const;
	virtual Vector2& operator+=(const Vector2& other);
	virtual Vector2& operator-=(const Vector2& other);
	virtual Vector2 operator+(const Vector2& other);
	virtual Vector2 operator-(const Vector2& other);
};

struct BoundingBox
{
	Vector2 LefTop;
	Vector2 RightBottom;

	Vector2 Size;
};
