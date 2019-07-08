#pragma once

#include "../Component.h"

/// <summary>
/// 摩擦のコンポーネント
/// </summary>
class Friction : public Component
{
public:
	// コンストラクタ
	Friction();
	// デストラクタ
	~Friction();

public:
	// 遅延更新処理
	void LateUpdate(float elapsedTime) override;

	// 衝突時の処理
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	DirectX::SimpleMath::Vector3 m_normal;
	bool m_isHit;
};