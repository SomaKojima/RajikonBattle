#pragma once
#include "../GameObject.h"

class Wall : public GameObject
{
public:
	// コンストラクタ
	Wall();
	// デストラクタ
	~Wall();

public:
	// 生成関数
	void Instance() override;
};
