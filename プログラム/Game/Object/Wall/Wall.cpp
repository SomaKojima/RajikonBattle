#include "../../../pch.h"
#include "Wall.h"
#include "../../Component/Collision/CollisionMesh.h"
#include "../../Component/Object/Wall/WallReflection.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Wall::Wall()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{
}

/// <summary>
/// ����
/// </summary>
void Wall::Instance()
{
	// ���O��ݒ肷��
	SetName("Wall");
	SetTag(Tag::Tag_Room);
	// ���b�V���̓����蔻����쐬
	Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\Wall.obj", 500.0f);
	AddComponent(collisionMesh);

	// �ǂ̔��˂��쐬
	Component* wallReflection = new WallReflection();
	AddComponent(wallReflection);
}
