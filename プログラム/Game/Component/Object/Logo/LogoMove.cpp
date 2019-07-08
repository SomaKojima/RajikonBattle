#include "../../../../pch.h"
#include "LogoMove.h"
#include "../../Render/TwoDimentionSprite.h"
#include "../../../Scene/SceneManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
LogoMove::LogoMove(TwoDimentionSprite * sprite, RECT rect)
	:
	m_sprite(sprite),
	m_rect(rect),
	m_animationTime(0.0f),
	m_flameNum(0),
	m_flameMaxNum(25),
	m_width(0),
	m_height(0),
	m_time(0)
{
	m_width = m_rect.right / 5;
	m_height = m_rect.bottom / 5;
}

/// <summary>
/// デストラクタ
/// </summary>
LogoMove::~LogoMove()
{
}

/// <summary>
/// 更新
/// </summary>
void LogoMove::Update(float elapsedTime)
{

	if (m_animationTime > 0.1f)
	{
		m_animationTime = 0.0f;
		if (m_flameNum < m_flameMaxNum - 1)
		{
			m_flameNum++;
		}
	}

	if (m_flameNum >= m_flameMaxNum - 1)
	{
		if (m_time > 2.0f)
		{
			SceneManager& sceneManager = SceneManager::GetInstace();
			sceneManager.ChangeSceneID(SceneManager::SceneID::Title);
		}
		m_time += elapsedTime;
	}

	// 描画場所（UV）の更新
	if (m_sprite)
	{
		int row;	//ロゴの行
		int column;//ロゴの列
		column = m_flameNum % 5;
		row = m_flameNum / 5;

		RECT rect{m_width * column , m_height * row, m_width * column + m_width, m_height * row + m_height};
		m_sprite->SetRECT(rect);
	}

	m_animationTime += elapsedTime;
}
