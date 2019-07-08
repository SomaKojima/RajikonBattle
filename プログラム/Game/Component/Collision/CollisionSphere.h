/// <summary>
/// CollisionSphere.h
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
//#include "../Component.h"
#include "CollisionComponent.h"
#include "../../Collision/DebugCollision/DebugSphere.h"
#include "../../Collision/Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class CollisionSphere : public CollisionComponent
{
public:
	CollisionSphere(DirectX::SimpleMath::Vector3 centerPos, float radius);
	~CollisionSphere();

	// ������
	void Initialize() override;

	// �X�V
	void Update(float elapsedTime) override;
	// �x���X�V
	void LateUpdate(float elapsedTime) override;
	// �`��
	void Render() override;
	// �I��
	void Finalize() override;

	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;
	
	// �Ǎ���
	void HitBack(const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);

	// �Ǎ���̌v�Z
	DirectX::SimpleMath::Vector3 WallCulc(const DirectX::SimpleMath::Vector3& normal, DirectX::SimpleMath::Vector3 vel, bool boundFlag = false);

	// �v���p�e�B
	DirectX::SimpleMath::Vector3 GetCenterPos() { return m_centerPos; }

	void SetBound(bool isBound) { m_isBound = isBound; }
private:
	DirectX::SimpleMath::Vector3 m_centerPos; // ���̒��S

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugSphere> m_obj;
	bool m_isBound;
};
