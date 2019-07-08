#pragma once

#include <vector>
#include <list>
#include "../Utility/BidirectionalList.h"
#include "../Utility/Singleton.h"
#include "../Data/Data.h"
#include "../Collision/CollisionObject.h"



class CollisionObjectList : public BidirectionalList<MyCollisionObject::CollisionObject>::RegisterTo
{
public:
	CollisionObjectList() {};
	~CollisionObjectList() {};
};

class CollisionManager : public Singleton<CollisionManager>
{
public:
	// コンストラクタ
	CollisionManager();
	// デストラクタ
	~CollisionManager();

	// 初期化
	void Initialize();
	// 更新
	void Update(float elapsedTime);

	/// <summary>
	/// レイ（線分）と衝突したオブジェクトを取得する
	/// </summary>
	/// <param name="segment"></param>
	/// <returns></returns>
	std::list<MyCollisionObject::CollisionObject*> RayGetCollision(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir, 
		float length, unsigned int cast = 0);

	// 管理に追加
	void Add(MyCollisionObject::CollisionObject& collisionObject, Tag tag);

	// 当たり判定のタグ管理の初期化
	void InitCollisionMatrix();
	// 当たり判定のタグ管理の取得
	bool GetCollisionMatrix(Tag tag1, Tag tag2);
	// 当たり判定のタグ管理の設定
	void SetCollisionMatrix(Tag tag1, Tag tag2, bool flag);

private:
	CollisionObjectList m_collisionObjectList[Tag::Tag_Max];
	std::vector<std::vector<bool>> m_collisionMatrix;
};