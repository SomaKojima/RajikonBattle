#pragma once

#include "../../Component.h"

class TwoDimentionSprite;

/// <summary>
/// タイトルロゴの動きのコンポーネント
/// </summary>
class LogoMove : public Component
{
public:
	// コンストラクタ
	LogoMove(TwoDimentionSprite* sprite, RECT rect);
	// デストラクタ
	~LogoMove();

public:
	// 更新処理
	void Update(float elapsedTime) override;

private:
	TwoDimentionSprite* m_sprite;
	RECT m_rect;
	float m_animationTime;
	int m_flameNum;
	int m_flameMaxNum;
	int m_width;
	int m_height;

	float m_time;
};
