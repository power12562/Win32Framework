#include "Collision.h"

bool Collision::CheckCollisionAABB(const BoundingBox& A,const BoundingBox& B)
{
	if (A.LefTop.Y < B.RightBottom.Y || A.RightBottom.Y > B.LefTop.Y || A.RightBottom.X < B.LefTop.X || A.LefTop.X > B.RightBottom.X)
	{
		return false;
	}
	return true;
}

bool Collision::CheckCollisionAABB(const BoundingBox& A, const Vector2& B)
{
	if (A.LefTop.Y < B.Y || A.RightBottom.Y > B.Y || A.RightBottom.X < B.X || A.LefTop.X > B.X)
	{
		return false;
	}
	return true;
}
