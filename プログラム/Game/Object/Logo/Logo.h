#pragma once
#include "../GameObject.h"

class Logo : public GameObject
{
public:
	// コンストラクタ
	Logo();
	// デストラクタ
	~Logo();

public:
	// 生成関数
	void Instance() override;
};