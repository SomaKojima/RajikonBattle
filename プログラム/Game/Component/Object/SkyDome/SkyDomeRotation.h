#pragma once

#include "../../Component.h"

/// <summary>
/// タイトルロゴの動きのコンポーネント
/// </summary>
class SkyDomeRotation : public Component
{
	static const float ROTATION;
public:
	// コンストラクタ
	SkyDomeRotation();
	// デストラクタ
	~SkyDomeRotation();

public:
	// 更新処理
	void Update(float elapsedTime) override;

private:
	float m_rotation;
};