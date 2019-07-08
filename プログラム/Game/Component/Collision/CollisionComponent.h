/// <summary>
/// CollisionComponent.h
/// 
/// 制作日:2018/10/26
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component.h"
#include "../../Collision/CollisionObject.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent(MyCollisionObject::CollisionObject* collisionObject);
	~CollisionComponent();

	// 終了処理
	void Finalize() override;

	MyCollisionObject::CollisionObject* GetCollisionObject() { return m_collisionObject; }

protected:
	MyCollisionObject::CollisionObject* m_collisionObject;
};
