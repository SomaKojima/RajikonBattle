#pragma once
#include "../GameObject.h"

class ResultStr : public GameObject
{
public:
	enum Type
	{
		You,
		Npc,
		Time
	};
public:
	// コンストラクタ
	ResultStr();
	// デストラクタ
	~ResultStr();

public:
	// 生成関数
	void Instance(Type type);
};