#pragma once
#include "../GameObject.h"

class Wall : public GameObject
{
public:
	// �R���X�g���N�^
	Wall();
	// �f�X�g���N�^
	~Wall();

public:
	// �����֐�
	void Instance() override;
};
