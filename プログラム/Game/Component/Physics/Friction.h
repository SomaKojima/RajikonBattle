#pragma once

#include "../Component.h"

/// <summary>
/// ���C�̃R���|�[�l���g
/// </summary>
class Friction : public Component
{
public:
	// �R���X�g���N�^
	Friction();
	// �f�X�g���N�^
	~Friction();

public:
	// �x���X�V����
	void LateUpdate(float elapsedTime) override;

	// �Փˎ��̏���
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	DirectX::SimpleMath::Vector3 m_normal;
	bool m_isHit;
};