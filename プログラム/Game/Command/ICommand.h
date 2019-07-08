#pragma once

#include "../Object/GameObject.h"

/// <summary>
/// コマンドクラス
/// </summary>
class ICommand
{
public:
	// 実行関数
	virtual void Excute(GameObject& obj) = 0;
};