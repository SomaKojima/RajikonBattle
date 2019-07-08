#include "../../pch.h"
#include "EnemyBullet.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Collision/CollisionSphere.h"
#include "../../Component/Object/BulletLife.h"

#include"../../Data/Model/ModelData.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBullet::EnemyBullet()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBullet::~EnemyBullet()
{
}

/// <summary>
/// ����
/// </summary>
void EnemyBullet::Instance()
{
	SetTag(Tag::Tag_BulletPlayer2);
	// ���f���擾
	ModelData& modelData = BulletModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// ���̓����蔻����쐬
	CollisionSphere* collisionSphere = new CollisionSphere(Vector3::Zero, 0.5f);
	//collisionSphere->SetBound(true);
	AddComponent(collisionSphere);
	// �e�̎���
	BulletLife* bulletLife = new BulletLife();
	AddComponent(bulletLife);
}
