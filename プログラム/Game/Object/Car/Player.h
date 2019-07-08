#pragma once
#include "../GameObject.h"
#include "../../Component/Object/StatusHP.h"

class Player : public GameObject
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

public:
	// 生成関数
	void Instance() override;

private:
};