#pragma once
#include "../GameObject.h"

class Cannon : public GameObject
{
public:
	// コンストラクタ
	Cannon();
	// デストラクタ
	~Cannon();

public:
	// 生成関数
	void Instance() override;
};