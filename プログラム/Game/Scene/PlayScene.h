#pragma once
#include"SceneManager.h"

#include "../../ADX2/ADX2Le.h"

/// <summary>
/// プレイシーン
/// </summary>
class PlayScene : public Scene
{
public:
	// コンストラクタ
	PlayScene();
	// デストラクタ
	~PlayScene();

public:
	// 生成関数
	void Instance() override;

private:
	MyLibrary::ADX2Le* m_a;

	CriAtomExPlaybackId m_id;
};