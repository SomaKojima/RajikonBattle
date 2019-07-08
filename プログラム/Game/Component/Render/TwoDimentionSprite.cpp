#include "../../pch.h"
#include "TwoDimentionSprite.h"
#include "../../SubGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
TwoDimentionSprite::TwoDimentionSprite(ID3D11ShaderResourceView* texture, RECT rect,
	float depth, DirectX::XMVECTOR color)
	:
	m_visible(true),
	m_texture(texture),
	m_rect(rect),
	m_depth(depth),
	m_color(Vector4::One),
	m_scale(Vector2::One),
	m_origin(0.5f, 0.5f)
{
	XMStoreFloat4(&m_color, color);
}

/// <summary>
/// デストラクタ
/// </summary>
TwoDimentionSprite::~TwoDimentionSprite()
{
}

/// <summary>
/// 描画
/// </summary>
void TwoDimentionSprite::Render()
{
	if (m_visible && m_texture)
	{
		SubGame& subGame = SubGame::GetInstace();
		Vector3 pos = m_gameObject->GetTransform().WorldPos();

		XMVECTOR color = XMLoadFloat4(&m_color);
		Vector2 origin = Vector2((m_rect.right - m_rect.left) * m_origin.x, (m_rect.bottom - m_rect.top) * m_origin.y);
		subGame.GetGame()->GetSpriteBatch()->Draw(m_texture, Vector2(pos.x, pos.y), &m_rect, color,
			0.0f, origin, m_scale, DirectX::SpriteEffects_None, m_depth);
	}
}

/// <summary>
/// 終了
/// </summary>
void TwoDimentionSprite::Finalize()
{
}

RECT TwoDimentionSprite::GetScreenRECT()
{
	Vector3 pos = m_gameObject->GetTransform().WorldPos();
	int width = m_rect.right - m_rect.left;
	int height = m_rect.bottom - m_rect.top;
	RECT rect = { m_rect.left - (width / 2) , m_rect.top - (height / 2), m_rect.right - (width / 2), m_rect.bottom - (height / 2) };
	rect = RECT{ rect.left + (int)pos.x, rect.top + (int)pos.y, rect.right + (int)pos.x, rect.bottom + (int)pos.y };
	
	return rect;
}
