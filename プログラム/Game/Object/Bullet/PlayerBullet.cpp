#include "../../pch.h"
#include "PlayerBullet.h"

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
PlayerBullet::PlayerBullet()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBullet::~PlayerBullet()
{
}

/// <summary>
/// ����
/// </summary>
void PlayerBullet::Instance()
{
	SetName("Bullet");
	SetTag(Tag::Tag_BulletPlayer1);
	// ���f���擾
	ModelData& modelData = BulletModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// ���̓����蔻����쐬
	CollisionSphere* collisionSphere = new CollisionSphere(Vector3::Zero, 0.5f);
	AddComponent(collisionSphere);
	//// �d�͂̃R���|�[�l���g���쐬
	//Gravity* gravity = new Gravity();
	//gravity->SetGravity(8.0f);
	//AddComponent(gravity);
	// �e�̎���
	BulletLife* bulletLife = new BulletLife();
	AddComponent(bulletLife);
}
