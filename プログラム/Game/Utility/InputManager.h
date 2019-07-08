#pragma once

#include "Singleton.h"

class InputManager : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

public:
	void Update(float elapsedTime);

	DirectX::Keyboard::State& GetKeyboard() { return m_keyboard; }
	DirectX::Keyboard::KeyboardStateTracker& GetKeyboardTracker() { return m_keyboardTracker; }
	DirectX::Mouse::State& GetMouse() { return m_mouse; }
	DirectX::Mouse::ButtonStateTracker& GetMouseTracker() { return m_mouseTracker; }
private:
	DirectX::Keyboard::State m_keyboard;
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	DirectX::Mouse::State m_mouse;
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;
};