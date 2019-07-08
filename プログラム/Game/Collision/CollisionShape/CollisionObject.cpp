#include "../../pch.h"
#include "CollisionObject.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 衝突時のデータの構造体のコンストラクタ
/// </summary>
MyCollisionObject::CollisionData::CollisionData()
	:
	isHit(false),
	type(SHAPE_TYPE::SHAPE_TYPE_NONE),
	shape({ nullptr }),
	hitPos(Vector3::Zero)
{
}

/// <summary>
/// 当たり判定のオブジェクトのコンストラクタ
/// </summary>
/// <param name="_type"></param>
/// <param name="_shape"></param>
MyCollisionObject::CollisionObject::CollisionObject(SHAPE_TYPE _type)
	:
	type(_type)
{
	shape.sphere = nullptr;
}