#include "../../pch.h"
#include "LogoScene.h"
#include "../Object/Logo/Logo.h"

/// <summary>
/// コンストラクタ
/// </summary>
LogoScene::LogoScene()
{
}

/// <summary>
/// デストラクタ
/// </summary>
LogoScene::~LogoScene()
{
}

/// <summary>
/// 生成
/// </summary>
void LogoScene::Instance()
{
	// ロゴの作成
	GameObject* logo = new Logo();
	logo->Instance();
	m_gameObjectList.Add(logo);
}
