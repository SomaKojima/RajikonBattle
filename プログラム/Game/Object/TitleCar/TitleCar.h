#pragma once
#include "../GameObject.h"

class TitleCar : public GameObject
{
public:
	// �R���X�g���N�^
	TitleCar();
	// �f�X�g���N�^
	~TitleCar();

public:
	// �����֐�
	void Instance() override;
};