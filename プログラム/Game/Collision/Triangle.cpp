#include "../../pch.h"
#include "Triangle.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �O�p�`�̓����蔻��I�u�W�F�N�g�̃R���X�g���N�^
/// </summary>
MyCollisionObject::Triangle::Triangle()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_TRIANGLE)
{
	shape.triangle = this;
}

/// <summary>
/// �O�p�`�̓����蔻��̌`��ł̏���
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Triangle::HitCheckCollision(CollisionObject & col, Vector3& hitPos)
{
	// ���g�̃��b�V���̃f�[�^
	MyCollisionObject::Triangle& triangle = *shape.triangle;
	switch (col.type)
	{
		/// <summary>
		/// ���̓����蔻��
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
	{
		// ����̋��̃f�[�^
		MyCollisionObject::Sphere& sphere2 = *col.shape.sphere;
		if (Collision::HitCheck_Sphere_Triangle(sphere2, triangle, hitPos))return true;
	}
	break;
	}
	return false;
}

void MyCollisionObject::Triangle::Init()
{
	collisionData.Init();
}
