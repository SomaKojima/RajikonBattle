#pragma once
#include "../GameObject.h"

class ExitButton : public GameObject
{
public:
	// �R���X�g���N�^
	ExitButton();
	// �f�X�g���N�^
	~ExitButton();

public:
	// �����֐�
	void Instance() override;
};