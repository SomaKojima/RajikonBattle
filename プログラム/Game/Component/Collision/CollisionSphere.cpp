/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "CollisionSphere.h"
#include "../../SubGame.h"
#include "../../DebugString.h"
#include "../../Collision/CCell.h"
#include "../../Collision/CollisionManager.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="radius">���a</param>
CollisionSphere::CollisionSphere(DirectX::SimpleMath::Vector3 centerPos, float radius)
	:
	CollisionComponent(new MyCollisionObject::Sphere()),
	m_centerPos(centerPos),
	m_obj(nullptr),
	m_isBound(false)
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	sphere.radius = radius;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionSphere::~CollisionSphere()
{

}

/// <summary>
/// ������
/// </summary>
void CollisionSphere::Initialize()
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	//�@���W�̍X�V
	sphere.center = m_gameObject->GetTransform().WorldPos() + m_centerPos;

	m_collisionObject->SetGameObject(*m_gameObject);

	CollisionManager& collisionManager = CollisionManager::GetInstace();
	//collisionManager.Add(*m_collisionObject, m_gameObject->GetTag());
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionSphere::Update(float elapsedTime)
{
}

/// <summary>
/// �x���X�V
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionSphere::LateUpdate(float elapsedTime)
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	//�@���W�̍X�V
	sphere.center = m_gameObject->GetTransform().WorldPos() + m_centerPos;
	// ��ԓo�^
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	Vector3 pos = Vector3(sphere.center.x - sphere.radius, sphere.center.y - sphere.radius, sphere.center.z - sphere.radius);
	Vector3 pos2 = Vector3(sphere.center.x + sphere.radius, sphere.center.y + sphere.radius, sphere.center.z + sphere.radius);

	cLiner8TreeManager.Register(*m_collisionObject, pos, pos2);


	// �����I�Ƀ}�C�i�X��Y���ɂ͂����Ȃ��悤�ɂ���

	// ���W�̍X�V
	pos = m_gameObject->GetTransform().WorldPos();

	MyCollisionObject::Plane plane;
	plane.Set_Plane(Vector3::Up, Vector3::Zero);
	Vector3 normal(0, 1, 0);
	Vector3 hit;
	if (Collision::HitCheck_Sphere_Plane(sphere, plane, hit))
	{
		pos = hit + normal * sphere.radius;
		m_gameObject->GetTransform().WorldPos(pos);
	}
}
	
/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void CollisionSphere::Render()
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	Matrix world = Matrix::CreateTranslation(m_centerPos) * m_gameObject->GetTransform().WorldMatrix();
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugSphere>(SubGame::GetInstace().GetGame()->GetDevice(), m_centerPos, sphere.radius);
	}
	else
	{
		Game* game = SubGame::GetInstace().GetGame();
		//m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
/// <param name="entity">����</param>
void CollisionSphere::Finalize()
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	sphere.Remove();
}

void CollisionSphere::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	// ���g�̋��̃f�[�^
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	switch (collisionObject.type)
	{
		/// <summary>
		/// ���̏Փˏ���
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
		{
			// ����̋��̃f�[�^
			MyCollisionObject::Sphere& sphere2 = *collisionObject.shape.sphere;

			// ���̉����o��
			Vector3 dir = sphere.center - sphere2.center;
			dir.Normalize();
			Vector3 pos = hitPos + dir * (sphere.radius + sphere2.radius);
			m_gameObject->GetTransform().WorldPos(pos);
		}
		break;

		/// <summary>
		/// ���b�V���̏Փˏ���
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_MESH:
		{
			// ����̃��b�V���̃f�[�^
			MyCollisionObject::Mesh& mesh2 = *collisionObject.shape.mesh;
			for (auto ite = mesh2.triangles.begin(); ite != mesh2.triangles.end(); ite++)
			{
				if ((*ite)->collisionData.isHit)
				{
					// �Ǎ���
					HitBack(*(*ite), (*ite)->collisionData.hitPos);
				}
			}
		}
		break;

		/// <summary>
		/// ���b�V���̏Փˏ���
		/// </summary>
		case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_TRIANGLE:
		{
			// ����̃��b�V���̃f�[�^
			MyCollisionObject::Triangle& triangle2 = *collisionObject.shape.triangle;
			if (triangle2.collisionData.isHit)
			{
				// �Ǎ���
				HitBack(triangle2, triangle2.collisionData.hitPos);
			}
		}
		break;
	}
}


/// <summary>
/// �Ǎ���
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
void CollisionSphere::HitBack(const MyCollisionObject::Triangle & triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// �O�p�`�̖@�����擾
	Vector3 normal = Vector3(triangle.plane.a, triangle.plane.b, triangle.plane.c);
	Transform& transform = m_gameObject->GetTransform();
	// ���g�̋��̃f�[�^
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;

	// ���x�ŕǍ�����s��
	Vector3 w_vec_vel = WallCulc(normal, transform.WorldVel());
	transform.WorldVel(w_vec_vel);

	// ���W�̍X�V
	Vector3 pos = transform.WorldPos();
	Vector3 hit;
	Collision::HitCheck_Sphere_Plane(sphere, triangle.plane, hit);
	pos = hit + normal * sphere.radius;
	transform.WorldPos(pos);

	// �����x��Ǎ�����s�������x�ɂ���
	Vector3 w_vec_accel = WallCulc(normal, transform.WorldAccel());
	transform.WorldAccel(w_vec_accel);
}


/// <summary>
/// �Ǎ���̌v�Z
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
/// <param name="vel"></param>
/// <returns></returns>
Vector3 CollisionSphere::WallCulc(const DirectX::SimpleMath::Vector3& normal, DirectX::SimpleMath::Vector3 vel, bool boundFlag 
)
{
	// ���x���擾
	Vector3 vec = vel;

	float l = -vec.Dot(normal);
	if(l > 0.0f)
	{
		if (boundFlag)
		{
			return (vec + (2 * l * normal));
		}
		else
		{
			return vec + (l * normal);
		}
	}
	return vel;
}

