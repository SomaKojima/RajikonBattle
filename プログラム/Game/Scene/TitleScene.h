#pragma once
#include"SceneManager.h"

#include "../../ADX2/ADX2Le.h"
/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public Scene
{
public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene();

public:
	// 生成関数
	void Instance() override;

private:
	MyLibrary::ADX2Le* m_a;

	CriAtomExPlaybackId m_id;
};
