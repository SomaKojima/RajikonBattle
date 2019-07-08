#pragma once

#include "CollisionObject.h"

namespace MyCollisionObject
{
	/// <summary>
	/// ���̓����蔻��I�u�W�F�N�g
	/// </summary>
	class Sphere : public CollisionObject
	{
	public:
		// �R���X�g���N�^
		Sphere();

		// �����蔻��̌`��ł̏���
		bool HitCheckCollision(CollisionObject& col, DirectX::SimpleMath::Vector3& hitPos) override;
		void Init() override;

		// ���̐ݒ�
		void Set_Sphere(DirectX::SimpleMath::Vector3 _center, float _radius)
		{
			center = _center;
			radius = _radius;
		}

		DirectX::SimpleMath::Vector3 center;	// ���S���W
		float radius;	// ���a
	};
}