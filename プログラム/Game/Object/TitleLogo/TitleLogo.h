#pragma once
#include "../GameObject.h"

class TitleLogo : public GameObject
{
public:
	// �R���X�g���N�^
	TitleLogo();
	// �f�X�g���N�^
	~TitleLogo();

public:
	// �����֐�
	void Instance() override;
};