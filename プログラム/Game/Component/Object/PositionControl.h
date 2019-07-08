#pragma once

#include "../Component.h"

/// <summary>
/// 摩擦のコンポーネント
/// </summary>
class PositionControl : public Component
{
public:
	// コンストラクタ
	PositionControl();
	// デストラクタ
	~PositionControl();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	DirectX::SimpleMath::Vector3 m_normal;
	bool m_isHit;
	float m_time;
};