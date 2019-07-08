#include "../../../pch.h"
#include "Player.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Physics/Friction.h"
#include "../../Component/Controller/PlayerController.h"
#include "../../Component/Object/PositionControl.h"

#include "../../Component/Collision/CollisionSphere.h"

#include"../../Data/Model/ModelData.h"

#include "Cannon.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}

/// <summary>
/// �����֐�
/// </summary>
void Player::Instance()
{
	SetName("Player");
	SetTag(Tag::Tag_Player1);
	// ���f���擾
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// ���̓����蔻����쐬
	Component* collisionSphere = new CollisionSphere(Vector3::Zero,1.5f);
	AddComponent(collisionSphere);
	// ����̃R���|�[�l���g���쐬
	Component* playerController = new PlayerController();
	AddComponent(playerController);
	// ���C�̃R���|�[�l���g���쐬
	Component* friction = new Friction();
	AddComponent(friction);
	// �d�͂̃R���|�[�l���g���쐬
	Component* gravity = new Gravity();
	AddComponent(gravity);
	// �p������̃R���|�[�l���g���쐬
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
	// �̗͂̃R���|�[�l���g���쐬
	StatusHP* statusHP = new StatusHP(100);
	AddComponent(statusHP);

	// �q�̍쐬
	/*Cannon* cannon = new Cannon();
	cannon->Instance();
	AddChild(cannon);*/
}
