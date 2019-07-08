#pragma once

#include "../Component.h"

/// <summary>
/// 重力のコンポーネント
/// </summary>
class Gravity : public Component
{
public:
	// コンストラクタ
	Gravity();
	// デストラクタ
	~Gravity();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	void SetGravity(float gravity) { m_gravity = gravity; }

	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	bool m_isHit;
	float m_gravity;
	DirectX::SimpleMath::Vector3 m_dir;
};