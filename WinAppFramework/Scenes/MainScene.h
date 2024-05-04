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

	//GameObj
	GameObject_Square obj_rect;
	GameObject_Sprite obj_Sprite;

};

