#pragma once

#include "../../Component.h"

class TwoDimentionSprite;
class StatusHP;

/// <summary>
/// �^�C�g�����S�̓����̃R���|�[�l���g
/// </summary>
class HPBarManager : public Component
{
public:
	// �R���X�g���N�^
	HPBarManager(TwoDimentionSprite* sprite, RECT rect, StatusHP* statusHP);
	// �f�X�g���N�^
	~HPBarManager();

public:
	// �X�V����
	void Update(float elapsedTime) override;

private:
	RECT m_rect;
	TwoDimentionSprite* m_sprite;
	StatusHP* m_statusHP;
	float m_width;
};
