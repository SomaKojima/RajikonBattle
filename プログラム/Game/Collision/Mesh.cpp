#include "../../pch.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���b�V���̓����蔻��I�u�W�F�N�g�̃R���X�g���N�^
/// </summary>
MyCollisionObject::Mesh::Mesh()
	:
	CollisionObject(SHAPE_TYPE::SHAPE_TYPE_MESH)
{
	shape.mesh = this;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MyCollisionObject::Mesh::~Mesh()
{
	for (auto ite = triangles.begin(); ite != triangles.end(); ite++)
	{
		delete (*ite);
	}
}

/// <summary>
///���b�V���̓����蔻��̌`��ł̏���
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
bool MyCollisionObject::Mesh::HitCheckCollision(CollisionObject & col, Vector3& hitPos)
{
	// ���g�̃��b�V���̃f�[�^
	MyCollisionObject::Mesh& mesh = *shape.mesh;
	switch (col.type)
	{
		/// <summary>
		/// ���̓����蔻��
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
		// ����̋��̃f�[�^
		MyCollisionObject::Sphere& sphere2 = *col.shape.sphere;
		if (SphereCollision(sphere2, hitPos)) return true;
		break;
	}
	return false;
}

bool MyCollisionObject::Mesh::SphereCollision(Sphere & sphere, DirectX::SimpleMath::Vector3 & hitPos)
{
	bool isHit = false;
	DirectX::SimpleMath::Vector3 min = DirectX::SimpleMath::Vector3(sphere.center.x - sphere.radius, sphere.center.y - sphere.radius, sphere.center.z - sphere.radius);
	DirectX::SimpleMath::Vector3 max = DirectX::SimpleMath::Vector3(sphere.center.x + sphere.radius, sphere.center.y + sphere.radius, sphere.center.z + sphere.radius);
	std::list<Triangle*> t = triangles;
	for (auto ite = t.begin(); ite != t.end(); ite++)
	{
		Triangle& triangle = *(*ite);
		DirectX::SimpleMath::Vector3 normal((*ite)->plane.a, (*ite)->plane.b, (*ite)->plane.c);
		if (sphere.GetGameObject().GetTransform().WorldVel().Dot(normal) > 0) continue;
		if (Collision::HitCheck_Sphere_Triangle(sphere, triangle, hitPos))
		{
			// �O�p�`�ɂ��ꂼ��Փˏ���ݒ肷��
			triangle.collisionData.isHit = true;
			triangle.collisionData.shape = sphere.shape;
			triangle.collisionData.type = sphere.type;
			triangle.collisionData.hitPos = hitPos;
			isHit = true;
		}
	}
	return isHit;
}

void MyCollisionObject::Mesh::Init()
{
	collisionData.Init();
	// �O�p�`��o�^
	for (auto ite = triangles.begin(); ite != triangles.end(); ite++)
	{
		(*ite)->Init();
	}
}

void MyCollisionObject::Mesh::SetMesh(std::list<Triangle*> _triangles)
{
	triangles = _triangles;
	origin = DirectX::SimpleMath::Vector3::Zero;
	/*/// <summary>
	/// �O���[�v����
	/// </summary>
	for (auto ite = triangles.begin(); ite != triangles.end(); ite++)
	{
		DirectX::SimpleMath::Vector3 max, min;
		(*ite)->GetMinMaxPos(min, max);
		int elem1 = GetElem(origin, min);
		int elem2 = GetElem(origin, max);
		if (elem1 == elem2)
		{
			group[elem1].push_back(*ite);
		}
	}*/
}

int MyCollisionObject::Mesh::GetElem(Vector3 origin, Vector3 point)
{
	if (origin.x > point.x)
	{
		if (origin.z > point.z)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if (origin.z > point.z)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
	return 0;
}

//std::list<MyCollisionObject::Triangle*> MyCollisionObject::Mesh::GetGroup(Vector3 min, Vector3 max)
//{
//	int elem1 = GetElem(origin, min);
//	int elem2 = GetElem(origin, max);
//	std::list<MyCollisionObject::Triangle*> answer = group[0];
//	if (elem1 == elem2 && elem1 != 0)
//	{
//		std::list<MyCollisionObject::Triangle*> plus = group[elem1];
//		answer.insert(answer.end(), plus.begin(), plus.end());
//		return answer;
//	}
//	return triangles;
//}
