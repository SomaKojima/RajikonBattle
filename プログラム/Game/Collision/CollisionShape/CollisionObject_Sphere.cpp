#include "../../pch.h"
#include "CollisionObject_Sphere.h"
#include "../Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 球の当たり判定オブジェクトのコンストラクタ
/// </summary>
MyCollisionObject::Sphere::Sphere()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_SPHERE),
	center(Vector3::Zero),
	radius(0.0f)
{
	shape.sphere = this;
}

/// <summary>
/// 球の当たり判定の形状での処理
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Sphere::CollisionShape(CollisionObject& col)
{
	Vector3 hitPos;
	// 自身の球のデータ
	MyCollisionObject::Sphere& sphere = *shape.sphere;
	switch (col.type)
	{
		/// <summary>
		/// 球の当たり判定
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
	{
		// 相手の球のデータ
		MyCollisionObject::Sphere& sphere2 = *col.shape.sphere;

		if (Collision::HitCheck_Sphere_Sphere(sphere, sphere2, hitPos))
		{
			return true;
		}

	}
	break;

	/// <summary>
	/// メッシュの当たり判定
	/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_MESH:
	{

		// 相手のメッシュのデータ
		MyCollisionObject::Mesh& mesh2 = *col.shape.mesh;

		bool isHit = false;
		for (auto ite = mesh2.triangles.begin(); ite != mesh2.triangles.end(); ite++)
		{
			if (Collision::HitCheck_Sphere_Triangle(sphere, (*ite), hitPos))
			{
				// 三角形にそれぞれ衝突情報を設定する
				(*ite).collisionData.isHit = true;
				(*ite).collisionData.shape = sphere.shape;
				(*ite).collisionData.type = sphere.type;
				isHit = true;
			}
		}
		if (isHit) return true;
	}
	break;
	}
	return false;
}

