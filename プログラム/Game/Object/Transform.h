#pragma once

#include <list>

class GameObject;

/// <summary>
/// �ό`�̃N���X
/// </summary>
class Transform
{
public:
	// �R���X�g���N�^
	Transform();

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);

	// ���[���h���W�����W���擾
	void WorldPos(const DirectX::SimpleMath::Vector3& pos);
	const DirectX::SimpleMath::Vector3& WorldPos();

	// ���[���h���x���擾
	DirectX::SimpleMath::Vector3 WorldVel();
	void WorldVel(DirectX::SimpleMath::Vector3& vel);

	// ���[���h�����x���擾
	DirectX::SimpleMath::Vector3 WorldAccel();
	void WorldAccel(DirectX::SimpleMath::Vector3& accel);

	// ���[�J�����W�̌������擾����
	DirectX::SimpleMath::Quaternion LocalDir();
	void LocalDir(DirectX::SimpleMath::Quaternion& localDir);
	// ���[���h�������擾
	DirectX::SimpleMath::Quaternion WorldDir();
	void WorldDir(DirectX::SimpleMath::Quaternion& dir);

	// ���[�J�����W�̋t�������擾����
	DirectX::SimpleMath::Quaternion LocalInvDir();
	void LocalInvDir(DirectX::SimpleMath::Quaternion inv);
	// ���[���h�t�������擾
	DirectX::SimpleMath::Quaternion WorldInvDir();

	// ���[���h�}�g���N�X�擾
	DirectX::SimpleMath::Matrix WorldMatrix() { return m_worldMatrix; }
	void WorldMatrix(DirectX::SimpleMath::Matrix& matrix) { m_worldMatrix = matrix; }


	// ���g�̃Q�[���I�u�W�F�N�g��ݒ肷��
	void SetGameObject(GameObject* gameObject) { m_gameObject = gameObject; }
	// ���g�̃Q�[���I�u�W�F�N�g���擾
	GameObject* GetGameObject() { return m_gameObject; }

private:
	//// ���W�E���x�E�����x�̃��[�J�����W�̎擾�̌v�Z
	//DirectX::SimpleMath::Vector3 GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld);
	//// ���W�E���x�E�����x�̃��[�J�����W�̐ݒ�̌v�Z
	//DirectX::SimpleMath::Vector3 SetLocalToWorld(DirectX::SimpleMath::Vector3& local);

	// �q�̍��W���X�V����
	void UpdateChildPos(DirectX::SimpleMath::Vector3& pos);
	// �q���̃}�g���N�X���X�V����
	void UpdateChildMatrix(float elapsedTime);

	//DirectX::SimpleMath::Quaternion FromToRotation(DirectX::SimpleMath::Vector3& fromNormalize, DirectX::SimpleMath::Vector3& toNormalize);

private:
	DirectX::SimpleMath::Vector3 m_worldPos;		// ���W

	DirectX::SimpleMath::Vector3 m_worldVel;		// ���x
	DirectX::SimpleMath::Vector3 m_worldAccel;		// �����x
	DirectX::SimpleMath::Quaternion m_localDir;		// ����
	DirectX::SimpleMath::Quaternion m_localInvDir;	// �t����
	DirectX::SimpleMath::Matrix m_worldMatrix;		// �}�g���N�X

private:	
	GameObject* m_gameObject;				// ���g�̃Q�[���I�u�W�F�N�g
};