#pragma once
#include "..\Framework\ScenesBase.h"
#include "..\Framework\GameObject\GameObject.h"

class MainScene : public SceneBase
{
public:
	MainScene();
	~MainScene() = default;

private:
	int CLIENT_WIDTH;
	int CLIENT_HEIGHT;

	//GameLoop
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void Rendering() override;

	//Field
	float KenMoveSpeed = 250.f;
	GameObject_Sprite obj_Ken;
	Animation::Clip Ken_Idle = nullptr;
	Animation::Clip Ken_Walk = nullptr;
	Animation::Clip Ken_Attack = nullptr;
};

