#include "../../pch.h"
#include "CollisionObject_Sphere.h"
#include "../Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���̓����蔻��I�u�W�F�N�g�̃R���X�g���N�^
/// </summary>
MyCollisionObject::Sphere::Sphere()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_SPHERE),
	center(Vector3::Zero),
	radius(0.0f)
{
	shape.sphere = this;
}

/// <summary>
/// ���̓����蔻��̌`��ł̏���
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Sphere::CollisionShape(CollisionObject& col)
{
	Vector3 hitPos;
	// ���g�̋��̃f�[�^
	MyCollisionObject::Sphere& sphere = *shape.sphere;
	switch (col.type)
	{
		/// <summary>
		/// ���̓����蔻��
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
	{
		// ����̋��̃f�[�^
		MyCollisionObject::Sphere& sphere2 = *col.shape.sphere;

		if (Collision::HitCheck_Sphere_Sphere(sphere, sphere2, hitPos))
		{
			return true;
		}

	}
	break;

	/// <summary>
	/// ���b�V���̓����蔻��
	/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_MESH:
	{

		// ����̃��b�V���̃f�[�^
		MyCollisionObject::Mesh& mesh2 = *col.shape.mesh;

		bool isHit = false;
		for (auto ite = mesh2.triangles.begin(); ite != mesh2.triangles.end(); ite++)
		{
			if (Collision::HitCheck_Sphere_Triangle(sphere, (*ite), hitPos))
			{
				// �O�p�`�ɂ��ꂼ��Փˏ���ݒ肷��
				(*ite).collisionData.isHit = true;
				(*ite).collisionData.shape = sphere.shape;
				(*ite).collisionData.type = sphere.type;
				isHit = true;
			}
		}
		if (isHit) return true;
	}
	break;
	}
	return false;
}

