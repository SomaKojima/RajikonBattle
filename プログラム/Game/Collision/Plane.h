#pragma once

#include "CollisionObject.h"

namespace MyCollisionObject
{
	/// <summary>
	/// 面の当たり判定オブジェクト
	/// </summary>
	class Plane : public CollisionObject
	{
	public:
		//　コンストラクタ
		/// <summary>
		/// 面の当たり判定オブジェクトのコンストラクタ
		/// </summary>
		Plane();

		// 当たり判定の形状での処理
		bool HitCheckCollision(CollisionObject& col, DirectX::SimpleMath::Vector3& hitPos) override;
		void Init() override;

		// 面の設定
		void Set_Plane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point)
		{
			// 法線を正規化しておく
			normal.Normalize();
			a = normal.x;
			b = normal.y;
			c = normal.z;

			// dの計算
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		// 面の設定
		void Set_Plane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// 法線を決める
			DirectX::SimpleMath::Vector3 vec_a = pos2 - pos1;
			DirectX::SimpleMath::Vector3 vec_b = pos3 - pos2;

			DirectX::SimpleMath::Vector3 normal = vec_a.Cross(vec_b);
			Set_Plane(normal, pos1);
		}
		// 面の設定
		void Set_Plane(DirectX::SimpleMath::Quaternion dir, DirectX::SimpleMath::Vector3 point)
		{
			DirectX::SimpleMath::Vector3 normal = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, dir);

			a = normal.x;
			b = normal.y;
			c = normal.z;

			// dの計算
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}


		float a, b, c, d;		// ABC　＝　法線
	};
}