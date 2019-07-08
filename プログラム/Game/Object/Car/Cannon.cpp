#include "../../pch.h"
#include "Cannon.h"
#include "../../Component/Render/RenderThreeDimension.h"

#include"../../Data/Model/ModelData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Cannon::Cannon()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Cannon::~Cannon()
{
}

/// <summary>
/// ����
/// </summary>
void Cannon::Instance()
{
	GetTransform().WorldPos(DirectX::SimpleMath::Vector3(0.0f, 3.0f, 0.0f));
	// ���f���擾
	ModelData& modelData = CarCannonModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
}
