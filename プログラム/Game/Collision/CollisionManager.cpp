#include "../../pch.h"
#include "CollisionManager.h"
#include "Collision.h"

/// <summary>
/// コンストラクタ
/// </summary>
CollisionManager::CollisionManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// 初期化
/// </summary>
void CollisionManager::Initialize()
{
	InitCollisionMatrix();
	SetCollisionMatrix(Tag::Tag_Player1, Tag::Tag_Player1, false);
	SetCollisionMatrix(Tag::Tag_BulletPlayer1, Tag::Tag_BulletPlayer1, false);
	SetCollisionMatrix(Tag::Tag_BulletPlayer1, Tag::Tag_Player1, false);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionManager::Update(float elapsedTime)
{
	for (int i = 0; i < Tag::Tag_Max; i++)
	{
		for (int j = 0; j < Tag::Tag_Max; j++)
		{
			if (!GetCollisionMatrix((Tag)i, (Tag)j)) continue;

			BidirectionalList<MyCollisionObject::CollisionObject>* obj = m_collisionObjectList[i].GetTop();
			while (obj)
			{
				BidirectionalList<MyCollisionObject::CollisionObject>* obj2 = m_collisionObjectList[j].GetTop();
				while (obj2)
				{
					if (obj == obj2)
					{
						obj2 = obj2->GetNext();
						continue;
					}
					// 当たり判定の処理
					if (obj->GetElement().Collision(obj2->GetElement()))
					{
						GameObject& gameObject = obj->GetElement().GetGameObject();
						GameObject& gameObject2 = obj2->GetElement().GetGameObject();
						gameObject.OnCollision(gameObject2, obj2->GetElement(), obj->GetElement().collisionData.hitPos);
						gameObject2.OnCollision(gameObject, obj->GetElement(), obj2->GetElement().collisionData.hitPos);
					}
					obj2 = obj2->GetNext();
				}

				obj = obj->GetNext();
			}
		}
	}

}

/// <summary>
/// レイ（線分）と衝突したオブジェクトを取得する
/// </summary>
/// <param name="segment"></param>
/// <returns></returns>
std::list<MyCollisionObject::CollisionObject*> CollisionManager::RayGetCollision(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir,
	float length, unsigned int cast)
{
	MyCollisionObject::Segment segment;
	segment.pos = pos;
	segment.vec = dir * length;

	std::list<MyCollisionObject::CollisionObject*> list;
	list.resize(0);

	for (int i = 0; i < Tag::Tag_Max; i++)
	{
		if ((cast & (1 << i)) == (1 << i))
		{
			continue;
		}
		BidirectionalList<MyCollisionObject::CollisionObject>* listElement = m_collisionObjectList[i].GetTop();

		while (listElement)
		{
			if (segment.Collision(listElement->GetElement()))
			{
				list.push_back(&listElement->GetElement());
			}
			listElement = listElement->GetNext();
		}
	}
	return list;
}

/// <summary>
/// 追加
/// </summary>
/// <param name="collisionObject"></param>
/// <param name="tag"></param>
void CollisionManager::Add(MyCollisionObject::CollisionObject & collisionObject, Tag tag)
{
	m_collisionObjectList[tag].Add(&collisionObject);
}

/// <summary>
/// 当たり判定のタグ管理の初期化
/// </summary>
void CollisionManager::InitCollisionMatrix()
{
	m_collisionMatrix.resize(Tag::Tag_Max);
	for (int i = 0; i < Tag::Tag_Max; i++)
	{
		m_collisionMatrix[i].resize(Tag::Tag_Max - i, true);
	}

	SetCollisionMatrix(Tag::Tag_Player1, Tag::Tag_Player1, false);
	SetCollisionMatrix(Tag::Tag_Player2, Tag::Tag_Player2, false);
	SetCollisionMatrix(Tag::Tag_Room, Tag::Tag_Room, false);
	SetCollisionMatrix(Tag::Tag_BulletPlayer1, Tag::Tag_Player1, false);
}

/// <summary>
/// 当たり判定のタグ管理の取得
/// </summary>
/// <param name="tag1"></param>
/// <param name="tag2"></param>
/// <returns></returns>
bool CollisionManager::GetCollisionMatrix(Tag tag1, Tag tag2)
{
	if (tag1 <= tag2)
	{
		return m_collisionMatrix[tag1][Tag::Tag_Max - 1 - tag2];
	}
	else
	{
		return m_collisionMatrix[tag2][Tag::Tag_Max - 1 - tag1];
	}
	return false;
}

/// <summary>
/// 当たり判定のタグ管理の設定
/// </summary>
/// <param name="tag1"></param>
/// <param name="tag2"></param>
/// <param name="flag"></param>
void CollisionManager::SetCollisionMatrix(Tag tag1, Tag tag2, bool flag)
{
	if (tag1 <= tag2)
	{
		m_collisionMatrix[tag1][Tag::Tag_Max - 1 - tag2] = flag;
		return;
	}
	else
	{
		m_collisionMatrix[tag2][Tag::Tag_Max - 1 - tag1] = flag;
		return;
	}
	return;
}