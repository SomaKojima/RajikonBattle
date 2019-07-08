#pragma once

#include "../../Component.h"

/// <summary>
/// タイトルロゴの動きのコンポーネント
/// </summary>
class TitleLogoMove : public Component
{
public:
	// コンストラクタ
	TitleLogoMove(float y);
	// デストラクタ
	~TitleLogoMove();

public:
	// 更新処理
	void Update(float elapsedTime) override;

private:
	bool m_isFall;
	float m_y;
	float m_time;
};
