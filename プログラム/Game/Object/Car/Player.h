#pragma once
#include "../GameObject.h"
#include "../../Component/Object/StatusHP.h"

class Player : public GameObject
{
public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();

public:
	// �����֐�
	void Instance() override;

private:
};