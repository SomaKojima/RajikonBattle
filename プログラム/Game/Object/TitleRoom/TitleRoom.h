#pragma once
#include "../GameObject.h"

class TitleRoom : public GameObject
{
public:
	// �R���X�g���N�^
	TitleRoom();
	// �f�X�g���N�^
	~TitleRoom();

public:
	// �����֐�
	void Instance() override;
};
