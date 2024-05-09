#pragma once
#include "RenderSystem.h"
#include "AnimationSystem.h"
#include "DataType\Vector2.h"
#include "DataType\wString.h"

class GameObjectBase
{
	struct Transform
	{
		Vector2 position;
		Vector2 scale;
	};
public:

	GameObjectBase() { transform = { {0, 0}, {1, 1} }; }
	virtual ~GameObjectBase() = default;

	Transform transform;
private:

};
