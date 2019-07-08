#pragma once

#include "../Component.h"

/// <summary>
/// タイマーのコンポーネント
/// </summary>
class TimerCounter : public Component
{
public:
	static const int NUM_WIDTH;
	static const int NUM_HEIGHT;
	static const float TIMER;
	static const float START_TIMER;
public:
	// コンストラクタ
	TimerCounter(ID3D11ShaderResourceView* texture, RECT rect, float time = TIMER);
	// デストラクタ
	~TimerCounter();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	// 描画
	void Render()override;
	void DrawNum(int num, DirectX::SimpleMath::Vector2 pos);
	unsigned GetDigit(unsigned num);

	float GetTime() { return m_time; }
	float GetTimeMax() { return m_timeMax; }
	float GetStartTime() { return m_startTime; }
	void SetIsStop(bool flag) { m_isStop = flag; }

private:
	float m_time;
	float m_timeMax;
	float m_startTime;
	ID3D11ShaderResourceView* m_texture;			// テクスチャハンドル
	RECT m_rect;
	bool m_isStop;
};