#pragma once

#include "CollisionObject.h"
#include "Plane.h"

namespace MyCollisionObject
{

	/// <summary>
	/// 三角形の当たり判定オブジェクト
	/// </summary>
	class Triangle : public CollisionObject
	{
	public:
		// コンストラクタ
		Triangle();

		// 当たり判定の形状での処理
		bool HitCheckCollision(CollisionObject& col, DirectX::SimpleMath::Vector3& hitPos) override;
		void Init() override;

		// 三角形の設定
		void Set_Triangle(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// 3点を利用した平面を求める
			plane.Set_Plane(pos1, pos2, pos3);
			startPos[0] = pos1;
			startPos[1] = pos2;
			startPos[2] = pos3;
			for (int i = 0; i < 3; i++)
			{
				pos[i] = startPos[i];
			}
		}
		// 三角形の設定
		void Set_Triangle(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Quaternion dir)
		{
			pos[0] = DirectX::SimpleMath::Vector3::Transform(startPos[0], world);
			pos[1] = DirectX::SimpleMath::Vector3::Transform(startPos[1], world);
			pos[2] = DirectX::SimpleMath::Vector3::Transform(startPos[2], world);

			plane.Set_Plane(dir, pos[0]);
		}

		void Set_Triangle(const Triangle &triangle) 
		{ 
			this->pos[0] = triangle.pos[0];
			this->pos[1] = triangle.pos[1];
			this->pos[2] = triangle.pos[2];

			this->startPos[0] = triangle.startPos[0];
			this->startPos[1] = triangle.startPos[1];
			this->startPos[2] = triangle.startPos[2];

			this->plane = triangle.plane;
		}

		void GetMinMaxPos(DirectX::SimpleMath::Vector3& min, DirectX::SimpleMath::Vector3& max)
		{
			min = pos[0];
			max = pos[0];
			for (int i = 1; i < 3; i++)
			{
				if (pos[i].x < min.x)min.x = pos[i].x;
				else if (pos[i].x > max.x) max.x = pos[i].x;

				if (pos[i].y < min.y)min.y = pos[i].y;
				else if (pos[i].y > max.y) max.y = pos[i].y;

				if (pos[i].z < min.z)min.z = pos[i].z;
				else if (pos[i].z > max.z) max.z = pos[i].z;
			}
		}

		DirectX::SimpleMath::Vector3 pos[3];
		DirectX::SimpleMath::Vector3 startPos[3];
		Plane plane;
	};

}