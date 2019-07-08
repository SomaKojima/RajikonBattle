#pragma once

#include "../../Component.h"

/// <summary>
/// タイトルロゴの動きのコンポーネント
/// </summary>
class WallReflection : public Component
{
public:
	// コンストラクタ
	WallReflection();
	// デストラクタ
	~WallReflection();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	// 衝突時の処理
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	
};