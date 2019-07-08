#pragma once
#include "../GameObject.h"

class TimerCounter;

class LimitTimer : public GameObject
{
public:
	// コンストラクタ
	LimitTimer();
	// デストラクタ
	~LimitTimer();

	TimerCounter* GetTimeCounter() { return m_timerCounter; }

public:
	// 生成関数
	void Instance(float time);

private:
	TimerCounter* m_timerCounter;
};
