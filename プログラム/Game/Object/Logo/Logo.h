#pragma once
#include "../GameObject.h"

class Logo : public GameObject
{
public:
	// �R���X�g���N�^
	Logo();
	// �f�X�g���N�^
	~Logo();

public:
	// �����֐�
	void Instance() override;
};