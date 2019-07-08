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
	// コンストラクタ
	Room();
	// デストラクタ
	~Room();

public:
	// 生成関数
	void Instance(Type type);
};
