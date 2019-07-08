#include "../../pch.h"
#include "Sphere.h"
#include "Collision.h"

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
bool MyCollisionObject::Sphere::HitCheckCollision(CollisionObject & col, Vector3& hitPos)
{
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
		if (Collision::HitCheck_Sphere_Sphere(sphere, sphere2, hitPos)) return true;
	}
	break;

	/// <summary>
	/// �O�p�`�̓����蔻��
	/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_TRIANGLE:
	{
		// ����̋��̃f�[�^
		MyCollisionObject::Triangle& triangle2 = *col.shape.triangle;
		if (Collision::HitCheck_Sphere_Triangle(sphere, triangle2, hitPos)) return true;
	}
	break;

	/// <summary>
	/// ���b�V���̓����蔻��
	/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_MESH:
	{
		// ����̃��b�V���̃f�[�^
		MyCollisionObject::Mesh& mesh2 = *col.shape.mesh;
		if (mesh2.SphereCollision(sphere, hitPos)) return true;

	}
	break;
	}
	return false;
}

void MyCollisionObject::Sphere::Init()
{
	collisionData.Init();
}

