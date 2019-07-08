#pragma once

#include "CollisionObject.h"

namespace MyCollisionObject
{
	/// <summary>
	/// �ʂ̓����蔻��I�u�W�F�N�g
	/// </summary>
	class Plane : public CollisionObject
	{
	public:
		//�@�R���X�g���N�^
		/// <summary>
		/// �ʂ̓����蔻��I�u�W�F�N�g�̃R���X�g���N�^
		/// </summary>
		Plane();

		// �����蔻��̌`��ł̏���
		bool HitCheckCollision(CollisionObject& col, DirectX::SimpleMath::Vector3& hitPos) override;
		void Init() override;

		// �ʂ̐ݒ�
		void Set_Plane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point)
		{
			// �@���𐳋K�����Ă���
			normal.Normalize();
			a = normal.x;
			b = normal.y;
			c = normal.z;

			// d�̌v�Z
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		// �ʂ̐ݒ�
		void Set_Plane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// �@�������߂�
			DirectX::SimpleMath::Vector3 vec_a = pos2 - pos1;
			DirectX::SimpleMath::Vector3 vec_b = pos3 - pos2;

			DirectX::SimpleMath::Vector3 normal = vec_a.Cross(vec_b);
			Set_Plane(normal, pos1);
		}
		// �ʂ̐ݒ�
		void Set_Plane(DirectX::SimpleMath::Quaternion dir, DirectX::SimpleMath::Vector3 point)
		{
			DirectX::SimpleMath::Vector3 normal = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, dir);

			a = normal.x;
			b = normal.y;
			c = normal.z;

			// d�̌v�Z
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}


		float a, b, c, d;		// ABC�@���@�@��
	};
}