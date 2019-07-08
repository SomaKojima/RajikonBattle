#pragma once

#include "ICommand.h"

/// <summary>
/// �ړ��R�}���h�̃N���X
/// </summary>
namespace Command
{
	class Accel : public ICommand
	{
	public:
		static const float MOVE_SPEED;
	public:
		// �R���X�g���N�^
		Accel();
		// �f�X�g���N�^
		~Accel();

		// ���s�֐�
		void Excute(GameObject& obj) override;

		void SetDir(DirectX::SimpleMath::Vector3 dir) { m_dir = dir; }

	private:
		DirectX::SimpleMath::Vector3 m_dir;
	};
}
