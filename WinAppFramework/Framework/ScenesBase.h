#pragma once
#include ".\GameObject\GameObject.h"	
#include ".\DataType\Vector2.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "SceneManager.h"
#include "SoundSystem.h"

class SceneBase
{
public:
	SceneBase(int FixedUpdateToSec = 50);
	~SceneBase();

	void GameRun();
	void Finalize();

protected:

	QPCTime time;
	Input input;

	bool isGameEnd;

	virtual void Start() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void Rendering() = 0;

	typedef My::List<Animation::Clip>::Node* Clip;

private:
	float FixedUpdate_elapsedTime;
};