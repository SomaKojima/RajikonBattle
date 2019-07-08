#include "../../pch.h"
#include "CollisionObject.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �Փˎ��̃f�[�^�̍\���̂̃R���X�g���N�^
/// </summary>
MyCollisionObject::CollisionData::CollisionData()
	:
	isHit(false),
	type(SHAPE_TYPE::SHAPE_TYPE_NONE),
	shape({ nullptr }),
	hitPos(Vector3::Zero)
{
}

/// <summary>
/// �����蔻��̃I�u�W�F�N�g�̃R���X�g���N�^
/// </summary>
/// <param name="_type"></param>
/// <param name="_shape"></param>
MyCollisionObject::CollisionObject::CollisionObject(SHAPE_TYPE _type)
	:
	type(_type)
{
	shape.sphere = nullptr;
}