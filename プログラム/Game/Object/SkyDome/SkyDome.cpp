#include "../../../pch.h"
#include "SkyDome.h"
#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Object/SkyDome/SkyDomeRotation.h"

#include"../../Data/Model/ModelData.h"

/// <summary>
/// �R���X�g���N�g
/// </summary>
SkyDome::SkyDome()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SkyDome::~SkyDome()
{
}

/// <summary>
/// ����
/// </summary>
void SkyDome::Instance()
{
	// ���O��ݒ肷��
	SetName("SkyDome");
	// ���f���擾
	ModelData& modelData = SkyDomeModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	RenderThreeDimention* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Sky);
	//renderThreeDimention->SetEmissionColor(DirectX::SimpleMath::Vector3::One * 0.8f);
	AddComponent(renderThreeDimention);
	// �X�J�C�h�[���̉�]�R���|�[�l���g���쐬
	SkyDomeRotation* skyDomeRotation = new SkyDomeRotation();
	AddComponent(skyDomeRotation);
}
