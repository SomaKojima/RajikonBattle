#pragma once

#include <list>
#include "ICommand.h"

// �O���錾
namespace Command
{
	class Accel;
	class Shot;
}

class InputHandler
{
public:
	static const float SHOT_TIME;
public:
	// �R���X�g���N�^
	InputHandler();
	// �f�X�g���N�^
	~InputHandler();

public:

	// ���̓n���h�����擾
	std::list<ICommand*> GetInputHnadle(float elapsedTime);

private:
	// �ړ��R�}���h
	Command::Accel* m_move;
	// �e�����R�}���h
	Command::Shot* m_shot;

	float m_shotTime;

};