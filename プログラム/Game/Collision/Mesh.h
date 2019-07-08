#pragma once

#include <list>
#include "CollisionObject.h"
#include "Triangle.h"
#include "../Utility/Morton.h"

namespace MyCollisionObject 
{

	/// <summary>
	/// ���b�V���̓����蔻��I�u�W�F�N�g
	/// </summary>
	class Mesh : public CollisionObject
	{
	public:
		// �R���X�g���N�^
		Mesh();
		// �f�X�g���N�^
		~Mesh();

		// �����蔻��̌`��ł̏���
		bool HitCheckCollision(CollisionObject& col, DirectX::SimpleMath::Vector3& hitPos) override;
		bool SphereCollision(Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos);
		void Init() override;


		// ���b�V���̐ݒ�
		void SetMesh(std::list<Triangle*> _triangles);
		int GetElem(DirectX::SimpleMath::Vector3 origin, DirectX::SimpleMath::Vector3 point);
		//std::list<Triangle*> GetGroup(DirectX::SimpleMath::Vector3 min, DirectX::SimpleMath::Vector3 max);

		std::list<Triangle*> triangles;
		DirectX::SimpleMath::Vector3 origin;
	};
}
