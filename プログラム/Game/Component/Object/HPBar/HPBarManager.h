#pragma once

#include "../../Component.h"

class TwoDimentionSprite;
class StatusHP;

/// <summary>
/// タイトルロゴの動きのコンポーネント
/// </summary>
class HPBarManager : public Component
{
public:
	// コンストラクタ
	HPBarManager(TwoDimentionSprite* sprite, RECT rect, StatusHP* statusHP);
	// デストラクタ
	~HPBarManager();

public:
	// 更新処理
	void Update(float elapsedTime) override;

private:
	RECT m_rect;
	TwoDimentionSprite* m_sprite;
	StatusHP* m_statusHP;
	float m_width;
};
