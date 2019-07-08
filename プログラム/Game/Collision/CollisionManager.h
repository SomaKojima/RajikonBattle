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
	// �R���X�g���N�^
	CollisionManager();
	// �f�X�g���N�^
	~CollisionManager();

	// ������
	void Initialize();
	// �X�V
	void Update(float elapsedTime);

	/// <summary>
	/// ���C�i�����j�ƏՓ˂����I�u�W�F�N�g���擾����
	/// </summary>
	/// <param name="segment"></param>
	/// <returns></returns>
	std::list<MyCollisionObject::CollisionObject*> RayGetCollision(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir, 
		float length, unsigned int cast = 0);

	// �Ǘ��ɒǉ�
	void Add(MyCollisionObject::CollisionObject& collisionObject, Tag tag);

	// �����蔻��̃^�O�Ǘ��̏�����
	void InitCollisionMatrix();
	// �����蔻��̃^�O�Ǘ��̎擾
	bool GetCollisionMatrix(Tag tag1, Tag tag2);
	// �����蔻��̃^�O�Ǘ��̐ݒ�
	void SetCollisionMatrix(Tag tag1, Tag tag2, bool flag);

private:
	CollisionObjectList m_collisionObjectList[Tag::Tag_Max];
	std::vector<std::vector<bool>> m_collisionMatrix;
};