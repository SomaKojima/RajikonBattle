#pragma once

#include "../Component.h"

/// <summary>
/// �^�C�}�[�̃R���|�[�l���g
/// </summary>
class TimerCounter : public Component
{
public:
	static const int NUM_WIDTH;
	static const int NUM_HEIGHT;
	static const float TIMER;
	static const float START_TIMER;
public:
	// �R���X�g���N�^
	TimerCounter(ID3D11ShaderResourceView* texture, RECT rect, float time = TIMER);
	// �f�X�g���N�^
	~TimerCounter();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	// �`��
	void Render()override;
	void DrawNum(int num, DirectX::SimpleMath::Vector2 pos);
	unsigned GetDigit(unsigned num);

	float GetTime() { return m_time; }
	float GetTimeMax() { return m_timeMax; }
	float GetStartTime() { return m_startTime; }
	void SetIsStop(bool flag) { m_isStop = flag; }

private:
	float m_time;
	float m_timeMax;
	float m_startTime;
	ID3D11ShaderResourceView* m_texture;			// �e�N�X�`���n���h��
	RECT m_rect;
	bool m_isStop;
};