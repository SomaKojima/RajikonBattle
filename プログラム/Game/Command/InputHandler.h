#pragma once

#include <list>
#include "ICommand.h"

// 前方宣言
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
	// コンストラクタ
	InputHandler();
	// デストラクタ
	~InputHandler();

public:

	// 入力ハンドルを取得
	std::list<ICommand*> GetInputHnadle(float elapsedTime);

private:
	// 移動コマンド
	Command::Accel* m_move;
	// 弾を撃つコマンド
	Command::Shot* m_shot;

	float m_shotTime;

};