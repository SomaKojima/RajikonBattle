#pragma once

#include "ICommand.h"

/// <summary>
/// �㏸�R�}���h�̃N���X
/// </summary>
namespace Command
{
	class Shot : public ICommand
	{
	public:
		static const float SHOT_SPEED;
	public:
		// �R���X�g���N�^
		Shot();
		~Shot();

	public:
		// ���s�֐�
		void Excute(GameObject& obj) override;
	};
}
