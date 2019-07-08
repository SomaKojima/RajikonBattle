#pragma once

#include "ICommand.h"

/// <summary>
/// 移動コマンドのクラス
/// </summary>
namespace Command
{
	class Accel : public ICommand
	{
	public:
		static const float MOVE_SPEED;
	public:
		// コンストラクタ
		Accel();
		// デストラクタ
		~Accel();

		// 実行関数
		void Excute(GameObject& obj) override;

		void SetDir(DirectX::SimpleMath::Vector3 dir) { m_dir = dir; }

	private:
		DirectX::SimpleMath::Vector3 m_dir;
	};
}
