#pragma once
#include "../GameObject.h"

class TitleLogo : public GameObject
{
public:
	// コンストラクタ
	TitleLogo();
	// デストラクタ
	~TitleLogo();

public:
	// 生成関数
	void Instance() override;
};