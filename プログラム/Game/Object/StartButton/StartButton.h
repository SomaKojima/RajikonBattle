#pragma once
#include "../GameObject.h"

class StartButton : public GameObject
{
public:
	// �R���X�g���N�^
	StartButton();
	// �f�X�g���N�^
	~StartButton();

public:
	// �����֐�
	void Instance() override;
};