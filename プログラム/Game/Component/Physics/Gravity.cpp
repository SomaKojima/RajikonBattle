#include "../../../pch.h"
#include "Gravity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Gravity::Gravity()
	:
	m_isHit(false),
	m_gravity(9.8f),
	m_dir(Vector3::Down)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Gravity::~Gravity()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Gravity::Update(float elapsedTime)
{
	//float g = m_gravity / (60 * 60);
	// �I�u�W�F�N�g�̉��������v�Z
	Vector3 down = Vector3::Transform(Vector3::Down, m_gameObject->GetTransform().WorldDir());
	// �d�͉����x���v�Z
	Vector3 accel = down * 0.02f;

	// �I�u�W�F�N�g�̉����x�ɉ�����
	accel += m_gameObject->GetTransform().WorldAccel();
	m_gameObject->GetTransform().WorldAccel(accel);
}

void Gravity::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	
}