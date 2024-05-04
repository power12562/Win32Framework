#pragma once
#include <windows.h>
#include <cmath>

class MyTime
{
public:
	MyTime();
	~MyTime() = default;
	ULONGLONG GetDeltatime_ms() const { return deltaTime_ms; }
	double GetDeltatime() const { return deltaTime_ms / 1000.0; }
	void UpdateTime();

private:
	LONGLONG previousTime;
	ULONGLONG currentTime;
	ULONGLONG deltaTime_ms; //밀리세크 단위의 델타타임
};

class QPCTime
{

public:
	QPCTime();
	~QPCTime() = default; 
	void UpdateTime();
	const float GetFrameRate()
	{
		if (deltaTime_ms == 0) return 0;

		return ceil(((1000.0f / deltaTime_ms) * 1000.f) / 1000.f);
	}
	float GetDeltatime_ms() const { return deltaTime_ms; }
	float GetDeltatime() const { return deltaTime_ms / 1000.f; }

	int FixedUpdatePerSec = 50;
	float GetFixedDelta() const { return 1.f / (float)FixedUpdatePerSec; }

private:
	LARGE_INTEGER previousTime;
	LARGE_INTEGER currentTime;
	LARGE_INTEGER frequency;

	float deltaTime_ms = 0;
};