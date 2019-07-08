#pragma once
#include "CollisionObject.h"

namespace MyCollisionObject
{
	/// <summary>
	/// 線分の当たり判定オブジェクト
	/// </summary>
	class Segment : public CollisionObject
	{
	public:
		// コンストラクタ
		Segment();

		// 当たり判定の形状での処理
		bool CollisionShape(CollisionObject& col) override;

		// 線分の設定
		void Set_Segment(DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _vec)
		{
			pos = _pos;
			vec = _vec;
		}

		DirectX::SimpleMath::Vector3 pos;		// 始点
		DirectX::SimpleMath::Vector3 vec;		// ベクトル
	};
}
