
#pragma once

#include "CollisionComponent.h"
#include "../../Collision/DebugCollision/DebugMesh.h"


/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class CollisionMesh : public CollisionComponent
{
public:
	CollisionMesh(wchar_t* fil, float radius);
	~CollisionMesh();

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

private:
	// �u.obj�v�̃t�@�C����
	wchar_t* m_file;
	// �t�@�C�������������t���O
	bool m_isFile;

	// �����蔻��̋�Ԃɓo�^���邽�߂̔��a�i�o�E���f�B���O�j
	float m_radius;

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugMesh> m_obj;
};
