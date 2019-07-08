#include "../../../../pch.h"
#include "ExitButtonMove.h"
#include "../../Render/TwoDimentionSprite.h"
#include "../../../MouseCursor/MouseCurosrManager.h"
#include "../../../../DebugString.h"
#include "../../../Utility/InputManager.h"
#include "../../../Scene/SceneManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="rect"></param>
ExitButtonMove::ExitButtonMove(TwoDimentionSprite* sprite, RECT rect)
	:
	m_sprite(sprite),
	m_rect(rect),
	m_flashTime(0.0f),
	m_flash(false),
	m_scaleChange(false),
	m_scale(1.0f),
	m_changeSceneTime(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ExitButtonMove::~ExitButtonMove()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void ExitButtonMove::Update(float elapsedTime)
{
	// 点滅
	Flash(elapsedTime);

	// 拡縮
	ScaleChange(elapsedTime);

	if (m_flash)
	{
		m_changeSceneTime += elapsedTime;
			// 終了
			PostQuitMessage(0);
	}
}

/// <summary>
/// 点滅
/// </summary>
/// <param name="elapsedTime"></param>
void ExitButtonMove::Flash(float elapsedTime)
{
	if (!m_sprite) return;

	MouseCursorManager& mcm = MouseCursorManager::GetInstace();
	Vector2 mousePos = mcm.GetPos();
	Mouse::ButtonStateTracker mouseST = InputManager::GetInstace().GetMouseTracker();
	RECT rect = m_sprite->GetScreenRECT();
	// マウスカーソルがRECT内に入った場合
	if (rect.left <= mousePos.x &&
		rect.right >= mousePos.x &&
		rect.top <= mousePos.y &&
		rect.bottom >= mousePos.y)
	{
		if (mouseST.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			m_flash = true;
		}
	}

	if (m_flash)
	{
		m_scaleChange = false;
		if (m_flashTime > 0.1f)
		{
			m_flashTime = 0.0f;
			m_sprite->SetVisible(!m_sprite->GetVisible());
		}
		m_flashTime += elapsedTime;
	}
	else
	{
		m_sprite->SetVisible(true);
	}
}

/// <summary>
/// 拡縮
/// </summary>
/// <param name="elapsedTime"></param>
void ExitButtonMove::ScaleChange(float elapsedTime)
{
	if (!m_sprite) return;

	MouseCursorManager& mcm = MouseCursorManager::GetInstace();
	Vector2 mousePos = mcm.GetPos();
	RECT rect = m_sprite->GetScreenRECT();
	// マウスカーソルがRECT内に入った場合
	if (rect.left <= mousePos.x &&
		rect.right >= mousePos.x &&
		rect.top <= mousePos.y &&
		rect.bottom >= mousePos.y)
	{
		if (!m_scaleChange && !m_flash)
		{
			m_scaleChange = true;
		}
	}
	else
	{
		m_scaleChange = false;
		m_scaleTime = 0.0f;
	}

	if (m_scaleChange)
	{
		m_scale = 0.8f + 0.2f * abs(cos(m_scaleTime * 6));
		m_sprite->SetScale(m_scale);

		m_scaleTime += elapsedTime;
	}
	else
	{
		m_sprite->SetScale(1.0f);
	}
}