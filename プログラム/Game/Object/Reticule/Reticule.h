#pragma once
#include "../GameObject.h"

class Reticule : public GameObject
{
public:
	// コンストラクタ
	Reticule();
	// デストラクタ
	~Reticule();

public:
	// 生成関数
	void Instance() override;
};