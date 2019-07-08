#pragma once

#include <list>
#include "CollisionObject.h"
#include "Triangle.h"
#include "../Utility/Morton.h"

namespace MyCollisionObject 
{

	/// <summary>
	/// メッシュの当たり判定オブジェクト
	/// </summary>
	class Mesh : public CollisionObject
	{
	public:
		// コンストラクタ
		Mesh();
		// デストラクタ
		~Mesh();

		// 当たり判定の形状での処理
		bool HitCheckCollision(CollisionObject& col, DirectX::SimpleMath::Vector3& hitPos) override;
		bool SphereCollision(Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos);
		void Init() override;


		// メッシュの設定
		void SetMesh(std::list<Triangle*> _triangles);
		int GetElem(DirectX::SimpleMath::Vector3 origin, DirectX::SimpleMath::Vector3 point);
		//std::list<Triangle*> GetGroup(DirectX::SimpleMath::Vector3 min, DirectX::SimpleMath::Vector3 max);

		std::list<Triangle*> triangles;
		DirectX::SimpleMath::Vector3 origin;
	};
}
