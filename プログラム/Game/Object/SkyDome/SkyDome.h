#pragma once
#include "../GameObject.h"

class SkyDome : public GameObject
{
public:
	// �R���X�g���N�^
	SkyDome();
	// �f�X�g���N�^
	~SkyDome();

public:
	// �����֐�
	void Instance() override;
};
