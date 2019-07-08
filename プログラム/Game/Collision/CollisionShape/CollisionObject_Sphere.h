#pragma once
#include "CollisionObject.h"

namespace MyCollisionObject
{
	/// <summary>
	/// 球の当たり判定オブジェクト
	/// </summary>
	class Sphere : public CollisionObject
	{
	public:
		// コンストラクタ
		Sphere();

		// 当たり判定の形状での処理
		bool CollisionShape(CollisionObject& col) override;

		// 球の設定
		void Set_Sphere(DirectX::SimpleMath::Vector3 _center, float _radius)
		{
			center = _center;
			radius = _radius;
		}

		DirectX::SimpleMath::Vector3 center;	// 中心座標
		float radius;	// 半径
	};
}