// �t�@�C���̓ǂݍ���
#include "../../pch.h"
#include "Transform.h"
#include "../Utility/BidirectionalList.h"
#include "GameObject.h"
#include "GameObjectList.h"

// ���O��Ԃ̎g�p
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Transform::Transform()
	:
	m_worldPos(DirectX::SimpleMath::Vector3::Zero),
	m_worldVel(DirectX::SimpleMath::Vector3::Zero),
	m_worldAccel(DirectX::SimpleMath::Vector3::Zero),
	m_localDir(DirectX::SimpleMath::Quaternion::Identity),
	m_localInvDir(DirectX::SimpleMath::Quaternion::Identity),
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_gameObject(nullptr)
{
}

/// <summary>
/// ����������
/// </summary>
void Transform::Initialize()
{
	// �}�g���N�X���X�V
	m_worldMatrix = Matrix::CreateFromQuaternion(WorldDir()) * Matrix::CreateTranslation(m_worldPos);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	//�@���W�̍X�V
	m_worldVel += m_worldAccel;
	m_worldPos += m_worldVel;

	// �}�g���N�X���X�V
	m_worldMatrix = Matrix::CreateFromQuaternion(WorldDir()) * Matrix::CreateTranslation(m_worldPos);

	// �q���̃}�g���N�X���X�V
	UpdateChildMatrix(elapsedTime);
}

/// <summary>
/// �q���̃}�g���N�X���X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::UpdateChildMatrix(float elapsedTime)
{
	BidirectionalList<GameObject>* obj = m_gameObject->GetChildList().GetList().GetTop();
	while (obj)
	{
		Transform& transform = obj->GetElement().GetTransform();
		// ���W���X�V
		Vector3 pos = transform.WorldPos() + WorldVel();
		transform.WorldPos(pos);
		// �}�g���N�X���X�V
		Matrix matrix = Matrix::CreateFromQuaternion(transform.WorldDir()) * Matrix::CreateTranslation(transform.WorldPos());
		transform.WorldMatrix(matrix);

		obj = obj->GetNext();
	}
}

/// <summary>
/// �q���̍��W�̍X�V
/// </summary>
/// <param name="pos"></param>
void Transform::UpdateChildPos(DirectX::SimpleMath::Vector3 & pos)
{
	BidirectionalList<GameObject>* obj = m_gameObject->GetChildList().GetList().GetTop();
	while (obj)
	{
		Transform& transform = obj->GetElement().GetTransform();
		// ���W���X�V
		transform.WorldPos(transform.WorldPos() + pos);
		transform.UpdateChildPos(pos);

		obj = obj->GetNext();
	}
}

/// <summary>
/// ���W-----------------------------------------------------------------------------------------------------------
/// </summary>

/// <summary>
/// ���[���h���W�̐ݒ�
/// </summary>
/// <param name="pos"></param>
void Transform::WorldPos(const DirectX::SimpleMath::Vector3 & pos)
{
	UpdateChildPos(pos - m_worldPos);
	m_worldPos = pos;
}

/// <summary>
/// ���[���h���W�̎擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & Transform::WorldPos()
{
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		return parent.WorldPos() + m_worldPos;
	}
	return m_worldPos;
}


/// <summary>
/// ���x-----------------------------------------------------------------------------------------------------------
/// </summary>

/// <summary>
/// ���[���h���x�̎擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldVel()
{
	return m_worldVel;
}

/// <summary>
/// ���[���h���x�̐ݒ�
/// </summary>
/// <param name="vel"></param>
void Transform::WorldVel(DirectX::SimpleMath::Vector3 & vel)
{
	m_worldVel = vel;
}


/// <summary>
/// �����x-----------------------------------------------------------------------------------------------------------
/// </summary>

/// <summary>
/// ���[���h�����x�̎擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldAccel()
{
	return m_worldAccel;
}

/// <summary>
/// ���[���h�����x�̐ݒ�
/// </summary>
/// <param name="accel"></param>
void Transform::WorldAccel(DirectX::SimpleMath::Vector3 & accel)
{
	m_worldAccel = accel;
}


/// <summary>
/// ��]-----------------------------------------------------------------------------------------------------------
/// </summary>

DirectX::SimpleMath::Quaternion Transform::LocalDir()
{
	return m_localDir;
}

void Transform::LocalDir(DirectX::SimpleMath::Quaternion & localDir)
{
	m_localDir = localDir;
	m_localDir.Inverse(m_localInvDir);
}

/// <summary>
/// ���[���h�̌������擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::WorldDir()
{
	DirectX::SimpleMath::Quaternion q = m_localDir;
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		q = parent.WorldDir() * m_localDir;
	}
	return q;
}

/// <summary>
/// ���[���h�̌�����ݒ肷��
/// </summary>
/// <param name="dir"></param>
void Transform::WorldDir(DirectX::SimpleMath::Quaternion & dir)
{
	m_localDir = dir;
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		m_localDir = dir * parent.WorldInvDir();
	}
	m_localDir.Inverse(m_localInvDir);
}


/// <summary>
/// �t��]-----------------------------------------------------------------------------------------------------------
/// </summary>

DirectX::SimpleMath::Quaternion Transform::LocalInvDir()
{
	return m_localInvDir;
}

void Transform::LocalInvDir(DirectX::SimpleMath::Quaternion inv)
{
	m_localInvDir = inv;
}

DirectX::SimpleMath::Quaternion Transform::WorldInvDir()
{
	DirectX::SimpleMath::Quaternion q = m_localInvDir;
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		q = parent.WorldInvDir() * m_localInvDir;
	}
	return q;
}

/// <summary>
/// ���[�J�����W�̃}�g���N�X
/// </summary>
/// <returns></returns>
//DirectX::SimpleMath::Matrix Transform::LocalMatrix()
//{
//	if (m_gameObject->GetParent())
//	{
//		return Matrix::CreateFromQuaternion(LocalDir()) *Matrix::CreateTranslation(LocalPos());
//	}
//	return m_worldMatrix;
//}

/// <summary>
/// from ���� to �܂ł̉�]���v�Z����
/// </summary>
//DirectX::SimpleMath::Quaternion Transform::FromToRotation(DirectX::SimpleMath::Vector3& fromNormalize, DirectX::SimpleMath::Vector3& toNormalize)
//{
//	// �p�x�����߂�
//	float cosine = fromNormalize.Dot(toNormalize);
//	if (cosine > 1.0f) cosine = 1.0f;
//	else if (cosine < -1.0f) cosine = -1.0f;
//
//	float angle = acos(cosine);
//
//	// �������߂�
//	Vector3 axis = fromNormalize.Cross(toNormalize);
//	if (axis == Vector3::Zero)
//	{
//
//		// fromNormalize �� toNormalize ���������^���΂̏ꍇ
//		// Vector3::Forward �� fromNormalize �Ō��݂̉�]�����߂�
//		float cosineOrigin = Vector3::Forward.Dot(fromNormalize);
//		if (cosineOrigin > 1.0f) cosineOrigin = 1.0f;
//		else if (cosineOrigin < -1.0f) cosineOrigin = -1.0f;
//		float angleOrigin = acos(cosineOrigin);
//
//		Vector3 axisOrigin = Vector3::Forward.Cross(fromNormalize);
//
//		if (axisOrigin == Vector3::Zero)
//		{
//			// Vector3::Forward �� fromNormalize ���������^���΂̏ꍇ
//			// Quaternion::Identity �� 180�x��]������
//			if (cosineOrigin == -1.0f)
//			{
//				return Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(180.0f));
//			}
//			else
//			{
//				return Quaternion::Identity;
//			}
//		}
//
//
//		// ���݂̉�]����N�H�[�^�j�I�������߂�
//		Quaternion qOrigin = Quaternion::CreateFromAxisAngle(axisOrigin, angleOrigin);
//
//		if (cosine == -1.0f)
//		{
//			// 180�x��]������
//			axis = fromNormalize.Cross(Vector3::Transform(Vector3::Right, qOrigin));
//			return Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(180.0f));
//		}
//		else
//		{
//			// ���݂̉�]�̃N�H�[�^�j�I����Ԃ�
//			return qOrigin;
//		}
//	}
//
//	Quaternion q = Quaternion::CreateFromAxisAngle(axis, angle);
//
//	return q;
//}