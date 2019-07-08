#pragma once

#include "../../StepTimer.h"
#include "../../Game.h"
#include "../Object/GameObject.h"
#include "../Collision/Collision.h"
#include "../Collision/CollisionObject.h"

class CollisionComponent;

/// <summary>
/// �R���|�[�l���g�N���X
/// </summary>
class Component
{
protected:
	// �R���X�g���N�^
	Component() : m_gameObject(nullptr){}

public:
	// ���z�f�X�g���N�^
	virtual ~Component() {}

	// ������
	virtual void Initialize() {}
	// �X�V
	virtual void Update(float elapsedTime) {}
	// �x���X�V
	virtual void LateUpdate(float elapsedTime) {}
	// �`��
	virtual void Render() {}
	// �I��
	virtual void Finalize() {}

	// �����蔻��̏���
	virtual void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos) {}

	// �I�u�W�F�N�g��ݒ肷��
	void SetGameObjec(GameObject* obj) { m_gameObject = obj; }
	// �I�u�W�F�N�g���擾����
	GameObject* GetGameObject() { return m_gameObject; }
protected:
	// ���g�̃R���|�[�l���g���A�^�b�`���Ă���I�u�W�F�N�g
	GameObject* m_gameObject;
};