#pragma once
#include "../GameObject.h"

class EnemyBullet : public GameObject
{
public:
	// �R���X�g���N�^
	EnemyBullet();
	// �f�X�g���N�^
	~EnemyBullet();

public:
	// �����֐�
	void Instance() override;
};
