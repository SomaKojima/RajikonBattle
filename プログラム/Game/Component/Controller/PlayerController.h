#pragma once

#include "../Component.h"
#include "../../Command/InputHandler.h"
#include "../../Command/ICommand.h"

/// <summary>
/// プレイヤーの操作のコンポーネント
/// </summary>
class PlayerController : public Component
{
public:
	// コンストラクタ
	PlayerController();
	// デストラクタ
	~PlayerController();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	// 回転
	void Rotation();

	void SetIsStop(bool flag) { m_isStop = flag; }

private:
	InputHandler inputHnadler;
	bool m_isStop;
};