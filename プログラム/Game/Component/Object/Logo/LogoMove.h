#pragma once

#include "../../Component.h"

class TwoDimentionSprite;

/// <summary>
/// �^�C�g�����S�̓����̃R���|�[�l���g
/// </summary>
class LogoMove : public Component
{
public:
	// �R���X�g���N�^
	LogoMove(TwoDimentionSprite* sprite, RECT rect);
	// �f�X�g���N�^
	~LogoMove();

public:
	// �X�V����
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
