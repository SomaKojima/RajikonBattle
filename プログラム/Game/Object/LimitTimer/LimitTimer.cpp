#include "../../../pch.h"
#include "LimitTimer.h"
#include "../../Component/Object/TimeCounter.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
LimitTimer::LimitTimer()
	:
	m_timerCounter(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LimitTimer::~LimitTimer()
{
}

/// <summary>
/// ����
/// </summary>
void LimitTimer::Instance(float time)
{
	// �摜�̃f�[�^���擾����
	NumTexture& textureData = NumTexture::GetInstace();

	m_timerCounter = new TimerCounter(textureData.GetTexture(), textureData.GetRect(), time);
	AddComponent(m_timerCounter);
}
