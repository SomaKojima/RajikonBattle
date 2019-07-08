#include "../../pch.h"
#include "BulletLife.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BulletLife::BulletLife()
	:
	m_time(0.0f),
	m_buf(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BulletLife::~BulletLife()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void BulletLife::Update(float elapsedTime)
{
	m_time += elapsedTime;

	if (m_gameObject == nullptr)
	{
		int a = 0;
	}
	else
	if (m_time > 5.0f )
	{
		// ���Ԍo�߂Ŏ��g�̃I�u�W�F�N�g��j������
		m_gameObject->Delete();
	}
	//m_buf = m_gameObject;
}

/// <summary>
/// �Փ�
/// </summary>
/// <param name="obj"></param>
/// <param name="collisionObject"></param>
/// <param name="hitPos"></param>
void BulletLife::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	if (obj.GetTag() == Tag::Tag_Player2)
	{
		m_gameObject->Delete();
	}
}
