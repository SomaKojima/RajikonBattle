#include "../../../../pch.h"
#include "SkyDomeRotation.h"

const float SkyDomeRotation::ROTATION = 0.01f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkyDomeRotation::SkyDomeRotation()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SkyDomeRotation::~SkyDomeRotation()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void SkyDomeRotation::Update(float elapsedTime)
{
	DirectX::SimpleMath::Vector3 axis = DirectX::SimpleMath::Vector3::Up;
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, DirectX::XMConvertToRadians(ROTATION));
	m_gameObject->GetTransform().WorldDir(m_gameObject->GetTransform().WorldDir() * q);
}
