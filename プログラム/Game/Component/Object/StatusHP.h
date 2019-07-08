#pragma once

#include "../Component.h"

class PlayCamera;
class GameManager;

/// <summary>
/// 体力のコンポーネント
/// </summary>
class StatusHP : public Component
{
public:
	// コンストラクタ
	StatusHP(int hp);
	// デストラクタ
	~StatusHP();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

	int GetHP() { return m_hp; }
	int GetMaxHP() { return m_maxHp; }
	
	void SetIsStop(bool flag) { m_isStop = flag; }

private:
	int m_hp;
	int m_maxHp;
	bool m_isStop;
};