#include "../../pch.h"
#include "Triangle.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 三角形の当たり判定オブジェクトのコンストラクタ
/// </summary>
MyCollisionObject::Triangle::Triangle()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_TRIANGLE)
{
	shape.triangle = this;
}

/// <summary>
/// 三角形の当たり判定の形状での処理
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Triangle::HitCheckCollision(CollisionObject & col, Vector3& hitPos)
{
	// 自身のメッシュのデータ
	MyCollisionObject::Triangle& triangle = *shape.triangle;
	switch (col.type)
	{
		/// <summary>
		/// 球の当たり判定
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
	{
		// 相手の球のデータ
		MyCollisionObject::Sphere& sphere2 = *col.shape.sphere;
		if (Collision::HitCheck_Sphere_Triangle(sphere2, triangle, hitPos))return true;
	}
	break;
	}
	return false;
}

void MyCollisionObject::Triangle::Init()
{
	collisionData.Init();
}
