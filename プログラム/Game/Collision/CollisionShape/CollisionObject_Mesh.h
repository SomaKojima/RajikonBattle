#pragma once

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

		// �����蔻��̌`��ł̏���
		bool CollisionShape(CollisionObject& col) override;

		// ���b�V���̐ݒ�
		void SetMesh(std::list<Triangle> triangles)
		{
			triangles = triangles;
		}

		std::list<Triangle> triangles;
	};
}