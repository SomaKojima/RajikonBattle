#include "../../../pch.h"
#include "LimitTimer.h"
#include "../../Component/Object/TimeCounter.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// コンストラクタ
/// </summary>
LimitTimer::LimitTimer()
	:
	m_timerCounter(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
LimitTimer::~LimitTimer()
{
}

/// <summary>
/// 生成
/// </summary>
void LimitTimer::Instance(float time)
{
	// 画像のデータを取得する
	NumTexture& textureData = NumTexture::GetInstace();

	m_timerCounter = new TimerCounter(textureData.GetTexture(), textureData.GetRect(), time);
	AddComponent(m_timerCounter);
}
