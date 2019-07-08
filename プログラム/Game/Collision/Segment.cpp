#include "../../pch.h"
#include "Segment.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 線分の当たり判定オブジェクトのコンストラクタ
/// </summary>
MyCollisionObject::Segment::Segment()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_SEGMENT),
	pos(Vector3::Zero),
	vec(Vector3::Zero)
{
	shape.segment = this;
}

/// <summary>
/// 線分の当たり判定の形状での処理
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Segment::HitCheckCollision(CollisionObject & col, Vector3& hitPos)
{
	return false;
}

void MyCollisionObject::Segment::Init()
{
	collisionData.Init();
}
