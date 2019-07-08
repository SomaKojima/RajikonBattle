#pragma once

#include "BaseCamera.h"
#include "../Component/Component.h"

class GameObject;

/// <summary>
/// �^�C�g���V�[���̃J����
/// </summary>
class TitleCamera : public BaseCamera, public Component
{
private:
	float m_rotation;
public:
	// �R���X�g���N�^
	TitleCamera();

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
};