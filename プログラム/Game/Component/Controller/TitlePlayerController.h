#pragma once

#include "../Component.h"
#include "../../Command/InputHandler.h"
#include "../../Command/ICommand.h"

/// <summary>
/// �v���C���[�̑���̃R���|�[�l���g
/// </summary>
class TitlePlayerController : public Component
{
public:
	// �R���X�g���N�^
	TitlePlayerController();
	// �f�X�g���N�^
	~TitlePlayerController();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	// ��]
	void Rotation();

	// �ړ�
	void Move();

private:
	InputHandler inputHnadler;

	DirectX::SimpleMath::Quaternion m_originDir;
};