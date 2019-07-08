#include "../../pch.h"
#include "TitleCar.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Physics/Friction.h"
#include "../../Component/Controller/TitlePlayerController.h"
#include "../../Component/Object/PositionControl.h"

#include "../../Component/Collision/CollisionSphere.h"

#include"../../Data/Model/ModelData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleCar::TitleCar()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleCar::~TitleCar()
{
}

/// <summary>
/// ����
/// </summary>
void TitleCar::Instance()
{

	SetName("Player");
	SetTag(Tag::Tag_Player1);
	// ���f���擾
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// ���̓����蔻����쐬
	Component* collisionSphere = new CollisionSphere(Vector3::Zero, 1.5f);
	AddComponent(collisionSphere);
	// �^�C�g�����̑���
	Component* controller = new TitlePlayerController();
	AddComponent(controller);
	// �d�͂̃R���|�[�l���g���쐬
	Component* gravity = new Gravity();
	AddComponent(gravity);
	// ���C�̃R���|�[�l���g���쐬
	Component* friction = new Friction();
	AddComponent(friction);
	// �p������̃R���|�[�l���g���쐬
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
}
