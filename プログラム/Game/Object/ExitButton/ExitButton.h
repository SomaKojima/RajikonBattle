#pragma once
#include "../GameObject.h"

class ExitButton : public GameObject
{
public:
	// コンストラクタ
	ExitButton();
	// デストラクタ
	~ExitButton();

public:
	// 生成関数
	void Instance() override;
};