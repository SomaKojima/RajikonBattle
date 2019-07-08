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
	shape.sphere = nullptr;
}

/// <summary>
///	������
/// </summary>
void MyCollisionObject::CollisionData::Init()
{
	isHit = false;
	shape = { nullptr };
	type = MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_NONE;
	hitPos = Vector3::Zero;
}

/// <summary>
/// �����蔻��̃I�u�W�F�N�g�̃R���X�g���N�^
/// </summary>
/// <param name="_type"></param>
/// <param name="_shape"></param>
MyCollisionObject::CollisionObject::CollisionObject(SHAPE_TYPE _type)
	:
	type(_type),
	BidirectionalList<MyCollisionObject::CollisionObject>(this),
	gameObject(nullptr)
{
	shape.sphere = nullptr;
}

/// <summary>
/// �����蔻��̃I�u�W�F�N�g�̃f�X�g���N�^
/// </summary>
/// <param name="_type"></param>
/// <param name="_shape"></param>
MyCollisionObject::CollisionObject::~CollisionObject()
{
	this->Remove();
}

/// <summary>
/// �����蔻��̊֐�
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::CollisionObject::Collision(CollisionObject & col)
{

	Init();
	col.Init();

	Vector3 hitPos;
	if (HitCheckCollision(col, hitPos))
	{
		// ���g�̏Փˑ���i����j�̏���ݒ肷��
		collisionData.isHit = true;
		collisionData.shape = col.shape;
		collisionData.type = col.type;
		collisionData.hitPos = hitPos;

		// ����̏Փˑ���i���g�j�̏���ݒ肷��
		col.collisionData.isHit = true;
		col.collisionData.shape = shape;
		col.collisionData.type = type;
		col.collisionData.hitPos = hitPos;

		return true;
	}
	return false;
}

