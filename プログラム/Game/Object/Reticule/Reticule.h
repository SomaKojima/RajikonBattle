#pragma once
#include "../GameObject.h"

class Reticule : public GameObject
{
public:
	// �R���X�g���N�^
	Reticule();
	// �f�X�g���N�^
	~Reticule();

public:
	// �����֐�
	void Instance() override;
};