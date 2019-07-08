#pragma once
#include "../GameObject.h"

class TimerCounter;

class LimitTimer : public GameObject
{
public:
	// �R���X�g���N�^
	LimitTimer();
	// �f�X�g���N�^
	~LimitTimer();

	TimerCounter* GetTimeCounter() { return m_timerCounter; }

public:
	// �����֐�
	void Instance(float time);

private:
	TimerCounter* m_timerCounter;
};
