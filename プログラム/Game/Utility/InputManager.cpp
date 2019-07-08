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
	// キーボード・マウスの更新
	m_keyboard = Keyboard::Get().GetState();
	m_mouse = Mouse::Get().GetState();

	// トラッカーの更新
	m_keyboardTracker.Update(m_keyboard);
	m_mouseTracker.Update(m_mouse);
}
