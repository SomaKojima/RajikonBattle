#pragma once

#include "../Utility/BidirectionalList.h"
#include "../Object/GameObject.h"
#include "CCell.h"

namespace MyCollisionObject
{
	class Sphere;
	class Segment;
	class Plane;
	class Triangle;
	class Mesh;

	/// <summary>
	/// �`��
	/// </summary>
	enum SHAPE_TYPE
	{
		SHAPE_TYPE_NONE = -1,
		SHAPE_TYPE_SPHERE,
		SHAPE_TYPE_SEGMENT,
		SHAPE_TYPE_PLANE,
		SHAPE_TYPE_TRIANGLE,
		SHAPE_TYPE_MESH,

		SHAPE_TYPE_MAX
	};

	/// <summary>
	/// �`��f�[�^�̋��p��
	/// </summary>
	union Shape
	{
		Sphere* sphere;
		Segment* segment;
		Plane* plane;
		Triangle* triangle;
		Mesh* mesh;
	};

	/// <summary>
	/// �Փˎ��̃f�[�^�̍\����
	/// </summary>
	class CollisionData
	{
	public:
		// �R���X�g���N�^
		CollisionData();

		// ������
		void Init();

		// �Փ˂������ǂ���
		bool isHit;
		// �Փˑ���̌`��
		SHAPE_TYPE type;
		// �Փˑ���̌`��f�[�^
		Shape shape;
		// �Փˏꏊ
		DirectX::SimpleMath::Vector3 hitPos;
	};

	/// <summary>
	/// �����蔻��̃I�u�W�F�N�g
	/// </summary>
	class CollisionObject : public BidirectionalList<CollisionObject>
	{
	public:
		// �R���X�g���N�^
		CollisionObject(SHAPE_TYPE _type);
		// �f�X�g���N�^
		virtual ~CollisionObject();

		// �����蔻��̌`��ł̏���
		bool Collision(CollisionObject& col);
		virtual bool HitCheckCollision(CollisionObject& col, DirectX::SimpleMath::Vector3& hitPos) = 0;

		virtual void Init() = 0;

		// ���g�̃Q�[���I�u�W�F�N�g�̃A�N�Z�T��
		void SetGameObject(GameObject& _gameObject) { gameObject = &_gameObject; }
		GameObject& GetGameObject() { return *gameObject; }

	public:
		// ���g�̌`�󂪂Ȃɂ�
		SHAPE_TYPE type;
		// �Փˎ��̃f�[�^
		CollisionData collisionData;
		// ���g�̌`��̃f�[�^
		Shape shape;
		// ���g�̃Q�[���I�u�W�F�N�g
		GameObject* gameObject;
	};

}