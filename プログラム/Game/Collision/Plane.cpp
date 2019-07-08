#include "../../pch.h"
#include "Plane.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �ʂ̓����蔻��I�u�W�F�N�g�̃R���X�g���N�^
/// </summary>
MyCollisionObject::Plane::Plane()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_PLANE),
	a(0),
	b(0),
	c(0),
	d(0)
{
	shape.plane = this;
}

/// <summary>
/// �ʂ̓����蔻��̌`��ł̏���
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Plane::HitCheckCollision(CollisionObject & col, Vector3& hitPos)
{
	return false;
}

void MyCollisionObject::Plane::Init()
{
	collisionData.Init();
}