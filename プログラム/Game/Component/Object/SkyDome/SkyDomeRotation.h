#pragma once

#include "../../Component.h"

/// <summary>
/// �^�C�g�����S�̓����̃R���|�[�l���g
/// </summary>
class SkyDomeRotation : public Component
{
	static const float ROTATION;
public:
	// �R���X�g���N�^
	SkyDomeRotation();
	// �f�X�g���N�^
	~SkyDomeRotation();

public:
	// �X�V����
	void Update(float elapsedTime) override;

private:
	float m_rotation;
};