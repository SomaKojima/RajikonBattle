#pragma once

#include "../Component.h"

/// <summary>
/// �d�͂̃R���|�[�l���g
/// </summary>
class Gravity : public Component
{
public:
	// �R���X�g���N�^
	Gravity();
	// �f�X�g���N�^
	~Gravity();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	void SetGravity(float gravity) { m_gravity = gravity; }

	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	bool m_isHit;
	float m_gravity;
	DirectX::SimpleMath::Vector3 m_dir;
};