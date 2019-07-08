#include "../../pch.h"
#include "Enemy.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Physics/Friction.h"
#include "../../Component/Controller/EnemyControllerr.h"
#include "../../Component/Object/PositionControl.h"

#include "../../Component/Collision/CollisionSphere.h"

#include"../../Data/Model/ModelData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy(Transform* target)
	:
	m_target(target)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// ����
/// </summary>
void Enemy::Instance()
{
	SetName("Enemy");
	SetTag(Tag::Tag_Player2);
	// ���f���擾
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	RenderThreeDimention* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// ���̓����蔻����쐬
	CollisionSphere* collisionSphere = new CollisionSphere(Vector3::Zero, 1.5f);
	AddComponent(collisionSphere);
	// �d�͂̃R���|�[�l���g���쐬
	Gravity* gravity = new Gravity();
	AddComponent(gravity);
	// ���C�̃R���|�[�l���g���쐬
	Friction* friction = new Friction();
	AddComponent(friction);
	// �G�̑���̃R���|�[�l���g���쐬
	EnemyController* enemyController = new EnemyController(m_target);
	AddComponent(enemyController);
	// �p������̃R���|�[�l���g���쐬
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
	// �̗͂̃R���|�[�l���g���쐬
	StatusHP* statusHP = new StatusHP(100);
	AddComponent(statusHP);

}
