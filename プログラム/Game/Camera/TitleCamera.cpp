#include "../../pch.h"
#include "TitleCamera.h"
#include "CameraManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player"></param>
TitleCamera::TitleCamera()
	:
	m_rotation(0.0f)
{
}

/// <summary>
/// 初期化
/// </summary>
void TitleCamera::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void TitleCamera::Update(float elapsedTime)
{
	// カメラ管理のビューを更新する
	CameraManager& cameraManager = CameraManager::GetInstace();
	Vector3 pos = Vector3::Transform(Vector3(0.0f, 5.0f, 20.0f),Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(-m_rotation)));
	Vector3 target = Vector3(0.0f, 2.0f, 0.0f);
	cameraManager.SetView(Matrix::CreateLookAt(pos, target, Vector3::Up));

	m_rotation += 0.2f;
	if (m_rotation > 360)
	{
		m_rotation = 0.0f;
	}
}
