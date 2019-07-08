#pragma once

#include <vector>
#include <list>
#include "../Utility/Singleton.h"
#include "../Data/Data.h"
#include "../Collision/CollisionObject.h"
#include "../Utility/Morton.h"

class CLiner8TreeManager : public Morton<MyCollisionObject::CollisionObject>, public Singleton<CLiner8TreeManager>
{
public:
	CLiner8TreeManager();
	~CLiner8TreeManager();

	void InitCollisionMatrix();
	bool GetCollisionMatrix(Tag tag1, Tag tag2);
	void SetCollisionMatrix(Tag tag1, Tag tag2, bool flag);

	void HitCheck();

private:
	std::vector<std::vector<bool>> m_collisionMatrix;
};