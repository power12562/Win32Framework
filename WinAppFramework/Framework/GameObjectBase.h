#pragma once
#include "..\RenderSystem.h"
#include "..\AnimationSystem.h"
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
