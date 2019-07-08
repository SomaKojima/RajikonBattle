#pragma once

#include "../../Component.h"

class TwoDimentionSprite;

/// <summary>
/// �^�C�g�����S�̓����̃R���|�[�l���g
/// </summary>
class StartButtonMove : public Component
{
public:
	// �R���X�g���N�^
	StartButtonMove(TwoDimentionSprite* sprite, RECT rect);
	// �f�X�g���N�^
	~StartButtonMove();

public:
	// �X�V����
	void Update(float elapsedTime) override;

private:
	// �_��
	void Flash(float elapsedTime);
	// �g�k
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
