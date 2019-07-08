#include "../../pch.h"
#include "CollisionObject_Segment.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �����̓����蔻��I�u�W�F�N�g�̃R���X�g���N�^
/// </summary>
MyCollisionObject::Segment::Segment()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_SEGMENT),
	pos(Vector3::Zero),
	vec(Vector3::Zero)
{
	shape.segment = this;
}

/// <summary>
/// �����̓����蔻��̌`��ł̏���
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Segment::CollisionShape(CollisionObject& col)
{
	return false;
}
