#include "../../pch.h"
#include "CCell.h"
#include "../Object/GameObject.h"
#include "../../Game.h"
#include "Collision.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CLiner8TreeManager::CLiner8TreeManager()
{

}

CLiner8TreeManager::~CLiner8TreeManager()
{
}

void CLiner8TreeManager::InitCollisionMatrix()
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
	SetCollisionMatrix(Tag::Tag_BulletPlayer1, Tag::Tag_BulletPlayer1, false);
	SetCollisionMatrix(Tag::Tag_BulletPlayer2, Tag::Tag_Player2, false);
	SetCollisionMatrix(Tag::Tag_BulletPlayer2, Tag::Tag_BulletPlayer2, false);
}

bool CLiner8TreeManager::GetCollisionMatrix(Tag tag1, Tag tag2)
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

void CLiner8TreeManager::SetCollisionMatrix(Tag tag1, Tag tag2, bool flag)
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



void CLiner8TreeManager::HitCheck()
{
	// ƒŠƒXƒg‚ðŽæ“¾‚·‚é
	std::vector<MyCollisionObject::CollisionObject*> colVec;
	DWORD colNum = GetList(colVec);
	colNum /= 2;
	for (int i = 0; i < colNum; i++)
	{
		MyCollisionObject::CollisionObject* obj = colVec[i * 2];
		MyCollisionObject::CollisionObject* obj2 = colVec[i * 2 + 1];
		Tag tag = obj->GetElement().GetGameObject().GetTag();
		Tag tag2 = obj2->GetElement().GetGameObject().GetTag();
		if (!GetCollisionMatrix(tag, tag2))
		{
			continue;
		}
		// “–‚½‚è”»’è‚Ìˆ—
		if (obj->Collision(*obj2))
		{
			GameObject& gameObject = obj->GetGameObject();
			GameObject& gameObject2 = obj2->GetGameObject();
			gameObject.OnCollision(gameObject2, *obj2, obj->collisionData.hitPos);
			gameObject2.OnCollision(gameObject, *obj, obj2->collisionData.hitPos);
		}
	}

}

