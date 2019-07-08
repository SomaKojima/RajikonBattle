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
	// コンストラクタ
	HPBar();
	// デストラクタ
	~HPBar();

public:
	// 生成関数
	void Instance(GameObject* obj, TYPE type);
};