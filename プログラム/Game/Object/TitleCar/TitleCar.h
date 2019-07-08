#pragma once
#include "../GameObject.h"

class TitleCar : public GameObject
{
public:
	// コンストラクタ
	TitleCar();
	// デストラクタ
	~TitleCar();

public:
	// 生成関数
	void Instance() override;
};