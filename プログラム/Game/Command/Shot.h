#pragma once

#include "ICommand.h"

/// <summary>
/// 上昇コマンドのクラス
/// </summary>
namespace Command
{
	class Shot : public ICommand
	{
	public:
		static const float SHOT_SPEED;
	public:
		// コンストラクタ
		Shot();
		~Shot();

	public:
		// 実行関数
		void Excute(GameObject& obj) override;
	};
}
