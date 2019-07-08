#include "../../../../pch.h"
#include "WallReflection.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
WallReflection::WallReflection()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WallReflection::~WallReflection()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void WallReflection::Update(float elapsedTime)
{
}

/// <summary>
/// �Փ�
/// </summary>
void WallReflection::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	// �Փ˂�������̑��x�𔽓]������
	DirectX::SimpleMath::Vector3 vel = obj.GetTransform().WorldVel();
	obj.GetTransform().WorldVel(-vel);
	obj.GetTransform().WorldAccel(DirectX::SimpleMath::Vector3(0,0,0));
}
