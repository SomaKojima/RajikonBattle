#include "../../../../pch.h"
#include "WallReflection.h"

/// <summary>
/// コンストラクタ
/// </summary>
WallReflection::WallReflection()
{
}

/// <summary>
/// デストラクタ
/// </summary>
WallReflection::~WallReflection()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void WallReflection::Update(float elapsedTime)
{
}

/// <summary>
/// 衝突
/// </summary>
void WallReflection::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	// 衝突した相手の速度を反転させる
	DirectX::SimpleMath::Vector3 vel = obj.GetTransform().WorldVel();
	obj.GetTransform().WorldVel(-vel);
	obj.GetTransform().WorldAccel(DirectX::SimpleMath::Vector3(0,0,0));
}
