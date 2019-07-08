#include "../../../../pch.h"
#include "HPBarManager.h"
#include "../../Render/TwoDimentionSprite.h"
#include "../StatusHP.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sprite"></param>
/// <param name="rect"></param>
HPBarManager::HPBarManager(TwoDimentionSprite * sprite, RECT rect, StatusHP* statusHP)
	:
	m_sprite(sprite),
	m_rect(rect),
	m_statusHP(statusHP)
{
	m_width= m_rect.right - m_rect.left;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HPBarManager::~HPBarManager()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void HPBarManager::Update(float elapsedTime)
{
	if (m_statusHP && m_sprite)
	{
		m_rect.right = m_width * (m_statusHP->GetHP() / (float)m_statusHP->GetMaxHP());
		m_sprite->SetRECT(m_rect);

		if (m_statusHP->GetHP() <= 0)
		{
			m_statusHP = nullptr;
		}
	}
}
