#pragma once
#include "../GameObject.h"

class Room : public GameObject
{
public:
	enum Type
	{
	Title,
	Play
	};
public:
	// �R���X�g���N�^
	Room();
	// �f�X�g���N�^
	~Room();

public:
	// �����֐�
	void Instance(Type type);
};
