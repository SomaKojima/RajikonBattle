#pragma once

#include "../../Component.h"

/// <summary>
/// �^�C�g�����S�̓����̃R���|�[�l���g
/// </summary>
class WallReflection : public Component
{
public:
	// �R���X�g���N�^
	WallReflection();
	// �f�X�g���N�^
	~WallReflection();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	// �Փˎ��̏���
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;

private:
	
};