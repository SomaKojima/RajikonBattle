#pragma once
#include "../GameObject.h"

class StartButton : public GameObject
{
public:
	// コンストラクタ
	StartButton();
	// デストラクタ
	~StartButton();

public:
	// 生成関数
	void Instance() override;
};