#pragma once
#include "../GameObject.h"

class SkyDome : public GameObject
{
public:
	// コンストラクタ
	SkyDome();
	// デストラクタ
	~SkyDome();

public:
	// 生成関数
	void Instance() override;
};
