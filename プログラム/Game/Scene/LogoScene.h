#pragma once
#include"SceneManager.h"

/// <summary>
/// ロゴシーン
/// </summary>
class LogoScene : public Scene
{
public:
	// コンストラクタ
	LogoScene();
	// デストラクタ
	~LogoScene();

public:
	// 生成関数
	void Instance() override;
};
