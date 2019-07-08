#pragma once

#include "../Component.h"
#include "../../Command/InputHandler.h"
#include "../../Command/ICommand.h"

/// <summary>
/// プレイヤーの操作のコンポーネント
/// </summary>
class TitlePlayerController : public Component
{
public:
	// コンストラクタ
	TitlePlayerController();
	// デストラクタ
	~TitlePlayerController();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	// 回転
	void Rotation();

	// 移動
	void Move();

private:
	InputHandler inputHnadler;

	DirectX::SimpleMath::Quaternion m_originDir;
};