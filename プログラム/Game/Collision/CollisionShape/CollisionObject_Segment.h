#pragma once
#include "CollisionObject.h"

namespace MyCollisionObject
{
	/// <summary>
	/// �����̓����蔻��I�u�W�F�N�g
	/// </summary>
	class Segment : public CollisionObject
	{
	public:
		// �R���X�g���N�^
		Segment();

		// �����蔻��̌`��ł̏���
		bool CollisionShape(CollisionObject& col) override;

		// �����̐ݒ�
		void Set_Segment(DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _vec)
		{
			pos = _pos;
			vec = _vec;
		}

		DirectX::SimpleMath::Vector3 pos;		// �n�_
		DirectX::SimpleMath::Vector3 vec;		// �x�N�g��
	};
}
