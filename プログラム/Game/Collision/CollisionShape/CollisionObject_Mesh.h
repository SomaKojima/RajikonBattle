#pragma once

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

		// 当たり判定の形状での処理
		bool CollisionShape(CollisionObject& col) override;

		// メッシュの設定
		void SetMesh(std::list<Triangle> triangles)
		{
			triangles = triangles;
		}

		std::list<Triangle> triangles;
	};
}