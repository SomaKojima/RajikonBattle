#pragma once
#include "../GameObject.h"

class PlayerBullet : public GameObject
{
public:
	// �R���X�g���N�^
	PlayerBullet();
	// �f�X�g���N�^
	~PlayerBullet();

public:
	// �����֐�
	void Instance() override;
};
