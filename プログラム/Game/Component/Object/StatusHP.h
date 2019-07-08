#pragma once

#include "../Component.h"

class PlayCamera;
class GameManager;

/// <summary>
/// �̗͂̃R���|�[�l���g
/// </summary>
class StatusHP : public Component
{
public:
	// �R���X�g���N�^
	StatusHP(int hp);
	// �f�X�g���N�^
	~StatusHP();

public:
	// �X�V����
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