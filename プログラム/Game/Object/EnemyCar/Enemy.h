#pragma once
#include "../GameObject.h"
#include "../../Component/Object/StatusHP.h"

class PlayCamera;

class Enemy : public GameObject
{
public:
	// コンストラクタ
	Enemy(Transform* target);
	// デストラクタ
	~Enemy();

public:
	// 生成関数
	void Instance() override;
private:
	Transform* m_target;
};
