#pragma once
#include "../GameObject.h"

class Cannon : public GameObject
{
public:
	// �R���X�g���N�^
	Cannon();
	// �f�X�g���N�^
	~Cannon();

public:
	// �����֐�
	void Instance() override;
};