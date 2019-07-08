#pragma once

#include "../../Component.h"

class TwoDimentionSprite;

/// <summary>
/// タイトルロゴの動きのコンポーネント
/// </summary>
class StartButtonMove : public Component
{
public:
	// コンストラクタ
	StartButtonMove(TwoDimentionSprite* sprite, RECT rect);
	// デストラクタ
	~StartButtonMove();

public:
	// 更新処理
	void Update(float elapsedTime) override;

private:
	// 点滅
	void Flash(float elapsedTime);
	// 拡縮
	void ScaleChange(float elapsedTime);
private:
	RECT m_rect; 
	TwoDimentionSprite* m_sprite;
	float m_flashTime;
	bool m_flash;

	bool m_scaleChange;
	float m_scale;
	float m_scaleTime;

	float m_changeSceneTime;
};
