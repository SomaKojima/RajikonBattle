#pragma once
#include "../GameObject.h"

class ResultStr : public GameObject
{
public:
	enum Type
	{
		You,
		Npc,
		Time
	};
public:
	// �R���X�g���N�^
	ResultStr();
	// �f�X�g���N�^
	~ResultStr();

public:
	// �����֐�
	void Instance(Type type);
};