#pragma once

#include "../Component.h"

/// <summary>
/// ���C�̃R���|�[�l���g
/// </summary>
class BulletLife : public Component
{
public:
	// �R���X�g���N�^
	BulletLife();
	// �f�X�g���N�^
	~BulletLife();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	// �Փ�
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	float m_time;
	GameObject* m_buf;
};
