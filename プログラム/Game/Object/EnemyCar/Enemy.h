#pragma once
#include "../GameObject.h"
#include "../../Component/Object/StatusHP.h"

class PlayCamera;

class Enemy : public GameObject
{
public:
	// �R���X�g���N�^
	Enemy(Transform* target);
	// �f�X�g���N�^
	~Enemy();

public:
	// �����֐�
	void Instance() override;
private:
	Transform* m_target;
};
