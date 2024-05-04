#pragma once
#include "Vector2.h"

namespace Collision
{
	bool CheckCollisionAABB(const BoundingBox& A, const BoundingBox& B);
	bool CheckCollisionAABB(const BoundingBox& A, const Vector2& B);
}