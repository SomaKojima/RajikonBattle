#pragma once
#include "../GameObject.h"

class PlayerBullet : public GameObject
{
public:
	// コンストラクタ
	PlayerBullet();
	// デストラクタ
	~PlayerBullet();

public:
	// 生成関数
	void Instance() override;
};
