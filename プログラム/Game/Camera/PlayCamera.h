#pragma once

#include "BaseCamera.h"
#include "../Component/Component.h"

class GameObject;

/// <summary>
/// �v���C�V�[���̃J����
/// </summary>
class PlayCamera : public BaseCamera, public Component
{
public:
	enum CAMERA_TYPE
	{
		PLAY,
		RESULT
	};
private:
	// �ǂ������鑊��
	GameObject* m_target;

	float m_y;

	float m_rotation;
	CAMERA_TYPE m_type;
public:
	// �R���X�g���N�^
	PlayCamera(GameObject* targe);

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;

	void PlayScene(float elapsedTime);

	void ResultScene(float elapsedTime);

	void SetTarget(GameObject* target) { m_target = target; }

	void SetType(CAMERA_TYPE type) { m_type = type; }
};