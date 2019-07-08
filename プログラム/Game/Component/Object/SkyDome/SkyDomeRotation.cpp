#include "../../../../pch.h"
#include "SkyDomeRotation.h"

const float SkyDomeRotation::ROTATION = 0.01f;

/// <summary>
/// コンストラクタ
/// </summary>
SkyDomeRotation::SkyDomeRotation()
{
}

/// <summary>
/// デストラクタ
/// </summary>
SkyDomeRotation::~SkyDomeRotation()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void SkyDomeRotation::Update(float elapsedTime)
{
	DirectX::SimpleMath::Vector3 axis = DirectX::SimpleMath::Vector3::Up;
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, DirectX::XMConvertToRadians(ROTATION));
	m_gameObject->GetTransform().WorldDir(m_gameObject->GetTransform().WorldDir() * q);
}
