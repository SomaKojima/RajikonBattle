#pragma once

#include "../Object/GameObject.h"

/// <summary>
/// �R�}���h�N���X
/// </summary>
class ICommand
{
public:
	// ���s�֐�
	virtual void Excute(GameObject& obj) = 0;
};