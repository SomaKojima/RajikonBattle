/// <summary>
/// CollisionComponent.h
/// 
/// �����:2018/10/26
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Component.h"
#include "../../Collision/CollisionObject.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent(MyCollisionObject::CollisionObject* collisionObject);
	~CollisionComponent();

	// �I������
	void Finalize() override;

	MyCollisionObject::CollisionObject* GetCollisionObject() { return m_collisionObject; }

protected:
	MyCollisionObject::CollisionObject* m_collisionObject;
};
