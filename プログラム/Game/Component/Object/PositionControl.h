#pragma once

#include "../Component.h"

/// <summary>
/// ���C�̃R���|�[�l���g
/// </summary>
class PositionControl : public Component
{
public:
	// �R���X�g���N�^
	PositionControl();
	// �f�X�g���N�^
	~PositionControl();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	DirectX::SimpleMath::Vector3 m_normal;
	bool m_isHit;
	float m_time;
};