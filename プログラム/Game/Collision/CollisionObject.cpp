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
	shape.sphere = nullptr;
}

/// <summary>
///	初期化
/// </summary>
void MyCollisionObject::CollisionData::Init()
{
	isHit = false;
	shape = { nullptr };
	type = MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_NONE;
	hitPos = Vector3::Zero;
}

/// <summary>
/// 当たり判定のオブジェクトのコンストラクタ
/// </summary>
/// <param name="_type"></param>
/// <param name="_shape"></param>
MyCollisionObject::CollisionObject::CollisionObject(SHAPE_TYPE _type)
	:
	type(_type),
	BidirectionalList<MyCollisionObject::CollisionObject>(this),
	gameObject(nullptr)
{
	shape.sphere = nullptr;
}

/// <summary>
/// 当たり判定のオブジェクトのデストラクタ
/// </summary>
/// <param name="_type"></param>
/// <param name="_shape"></param>
MyCollisionObject::CollisionObject::~CollisionObject()
{
	this->Remove();
}

/// <summary>
/// 当たり判定の関数
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::CollisionObject::Collision(CollisionObject & col)
{

	Init();
	col.Init();

	Vector3 hitPos;
	if (HitCheckCollision(col, hitPos))
	{
		// 自身の衝突相手（相手）の情報を設定する
		collisionData.isHit = true;
		collisionData.shape = col.shape;
		collisionData.type = col.type;
		collisionData.hitPos = hitPos;

		// 相手の衝突相手（自身）の情報を設定する
		col.collisionData.isHit = true;
		col.collisionData.shape = shape;
		col.collisionData.type = type;
		col.collisionData.hitPos = hitPos;

		return true;
	}
	return false;
}

