#pragma once

#include "../Component.h"
#include "../../Command/InputHandler.h"
#include "../../Command/ICommand.h"

/// <summary>
/// �v���C���[�̑���̃R���|�[�l���g
/// </summary>
class PlayerController : public Component
{
public:
	// �R���X�g���N�^
	PlayerController();
	// �f�X�g���N�^
	~PlayerController();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	// ��]
	void Rotation();

	void SetIsStop(bool flag) { m_isStop = flag; }

private:
	InputHandler inputHnadler;
	bool m_isStop;
};