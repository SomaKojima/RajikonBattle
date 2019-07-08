#pragma once
#include "../GameObject.h"

class EnemyBullet : public GameObject
{
public:
	// コンストラクタ
	EnemyBullet();
	// デストラクタ
	~EnemyBullet();

public:
	// 生成関数
	void Instance() override;
};
