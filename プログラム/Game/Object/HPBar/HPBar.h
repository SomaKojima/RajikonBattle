#pragma once
#include "../GameObject.h"

class HPBar : public GameObject
{
public:
	enum TYPE
	{
		Player,
		Enemy
	};
public:
	// �R���X�g���N�^
	HPBar();
	// �f�X�g���N�^
	~HPBar();

public:
	// �����֐�
	void Instance(GameObject* obj, TYPE type);
};