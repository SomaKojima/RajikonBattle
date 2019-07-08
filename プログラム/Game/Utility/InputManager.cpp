#include "../../pch.h"
#include "InputManager.h"

using namespace DirectX;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update(float elapsedTime)
{
	// �L�[�{�[�h�E�}�E�X�̍X�V
	m_keyboard = Keyboard::Get().GetState();
	m_mouse = Mouse::Get().GetState();

	// �g���b�J�[�̍X�V
	m_keyboardTracker.Update(m_keyboard);
	m_mouseTracker.Update(m_mouse);
}
