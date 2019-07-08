#pragma once

#include "../Component.h"

/// <summary>
/// 摩擦のコンポーネント
/// </summary>
class BulletLife : public Component
{
public:
	// コンストラクタ
	BulletLife();
	// デストラクタ
	~BulletLife();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	// 衝突
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	float m_time;
	GameObject* m_buf;
};
