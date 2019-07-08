#pragma once
#include "../GameObject.h"

class TitleRoom : public GameObject
{
public:
	// コンストラクタ
	TitleRoom();
	// デストラクタ
	~TitleRoom();

public:
	// 生成関数
	void Instance() override;
};
