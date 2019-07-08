#include "../../pch.h"
#include "InputHandler.h"
#include "../Utility/InputManager.h"

#include "Accel.h"
#include "Shot.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const float InputHandler::SHOT_TIME = 0.3f;

/// <summary>
/// コンストラクタ
/// </summary>
InputHandler::InputHandler()
{
	m_move = new Command::Accel();
	m_shot = new Command::Shot();
}

/// <summary>
/// デストラクタ
/// </summary>
InputHandler::~InputHandler()
{
	delete m_move;
	delete m_shot;
}

/// <summary>
/// 入力ハンドルを取得
/// </summary>
/// <returns></returns>
list<ICommand*> InputHandler::GetInputHnadle(float elapsedTime)
{
	list<ICommand*> commandList;

	InputManager& inputManager = InputManager::GetInstace();

	Keyboard::State key = inputManager.GetKeyboard();
	Keyboard::KeyboardStateTracker keyST = inputManager.GetKeyboardTracker();

	Mouse::State mouse = inputManager.GetMouse();
	Mouse::ButtonStateTracker mouseST = inputManager.GetMouseTracker();
	
	// 移動
	{
		Vector3 dir = Vector3::Zero;
		// Wキー
		if (key.W) dir += Vector3::Forward;
		// Aキー
		if (key.A) dir += Vector3::Left;
		// Sキー
		if (key.S) dir += Vector3::Backward;
		// Dキー
		if (key.D) dir += Vector3::Right;
		if (key.W || key.A || key.S || key.D)
		{
			dir.Normalize();
			m_move->SetDir(dir);
			commandList.push_back(m_move);
		}
	}

	// 弾を撃つ
	{
		if (mouseST.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			//commandList.push_back(m_shot);
		}
		if (mouse.leftButton)
		{
			m_shotTime += elapsedTime;
			if (m_shotTime > SHOT_TIME)
			{
				m_shotTime = 0.0f;
				commandList.push_back(m_shot);
			}
		}
		else
		{
			m_shotTime = SHOT_TIME;
		}
	}

	return commandList;
}
