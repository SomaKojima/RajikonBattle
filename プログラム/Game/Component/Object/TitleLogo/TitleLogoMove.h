#pragma once

#include "../../Component.h"

/// <summary>
/// �^�C�g�����S�̓����̃R���|�[�l���g
/// </summary>
class TitleLogoMove : public Component
{
public:
	// �R���X�g���N�^
	TitleLogoMove(float y);
	// �f�X�g���N�^
	~TitleLogoMove();

public:
	// �X�V����
	void Update(float elapsedTime) override;

private:
	bool m_isFall;
	float m_y;
	float m_time;
};
