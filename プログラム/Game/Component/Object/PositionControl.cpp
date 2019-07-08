#include "../../pch.h"
#include "PositionControl.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PositionControl::PositionControl()
	:
	m_isHit(false),
	m_time(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PositionControl::~PositionControl()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void PositionControl::Update(float elapsedTime)
{
	if (!m_isHit)
	{
		m_time += elapsedTime;
		if (m_time > 0.2f)
		{
			m_normal = Vector3::Up;
		}
		 
	}
	else
	{
		m_time = 0.0f;
	}
	// ���K������
	m_normal.Normalize();

	// ���g�̕ό`
	Transform& transform = m_gameObject->GetTransform();
	// �p�������킹
	Vector3 up = Vector3::Transform(Vector3::Up, transform.WorldDir());
	// ��]���v�Z
	Vector3 axis = up.Cross(m_normal);
	if (axis != Vector3::Zero && m_normal != Vector3::Zero)
	{
		// �p�x�����߂�
		float cosine = up.Dot(m_normal);
		if (cosine > 1.0f)
		{
			cosine = 1.0f;
		}

		float rot = acos(cosine);
		Quaternion from = transform.WorldDir();
		Quaternion to   = transform.WorldDir() * Quaternion::CreateFromAxisAngle(axis, rot);
		Quaternion q    = Quaternion::Slerp(from, to, 1.0f);
		transform.WorldDir(q);
	}
	m_isHit = false;
}

void PositionControl::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	if (obj.GetName() == "Stadium")
	{
		Vector3 dir = Vector3::Zero;
		switch (collisionObject.type)
		{
		case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_MESH:
			{
				MyCollisionObject::Mesh& mesh = *collisionObject.shape.mesh;
				for (auto ite = mesh.triangles.begin(); ite != mesh.triangles.end(); ite++)
				{
					if ((*ite)->collisionData.isHit)
					{
						dir += Vector3((*ite)->plane.a, (*ite)->plane.b, (*ite)->plane.c);
					}
				}
				dir.Normalize();
				m_isHit = true;
			}
			break;

		case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_TRIANGLE:
			{
				MyCollisionObject::Triangle& triangle = *collisionObject.shape.triangle;
				dir += Vector3(triangle.plane.a, triangle.plane.b, triangle.plane.c);
			}
			m_isHit = true;
			break;
		}

		m_normal = dir;
	}
}
