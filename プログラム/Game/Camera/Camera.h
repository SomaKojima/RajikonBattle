#pragma once
#include "../Object/GameObject.h"

class PlayCamera;

class Camera : public GameObject
{
public:
	// �R���X�g���N�^
	Camera();
	// �f�X�g���N�^
	~Camera();

	// �v���C�V�[���̃J����
	void InitializePlay(GameObject* player);
	// �^�C�g���V�[���̃J����
	void InitializeTitle();

public:
	// �����֐�
	void Instance() override;

	PlayCamera* GetPlayCamera() { return m_playCamera; }

private:
	PlayCamera* m_playCamera;
};