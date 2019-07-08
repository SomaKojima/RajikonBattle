#include "../../pch.h"
#include "Camera.h"
#include "PlayCamera.h"
#include "TitleCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="target"></param>
Camera::Camera()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// プレイシーンのカメラの初期化
/// </summary>
/// <param name="target"></param>
void Camera::InitializePlay(GameObject * target)
{
	// カメラのコンポーネントを作成
	m_playCamera = new PlayCamera(target);
	AddComponent(m_playCamera);
}

/// <summary>
/// タイトルシーンのカメラの初期化
/// </summary>
void Camera::InitializeTitle()
{
	Component* titleCamera = new TitleCamera();
	AddComponent(titleCamera);
}

/// <summary>
/// 生成関数
/// </summary>
void Camera::Instance()
{
}
