/// <summary>
/// Collision.h
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include <list>
#include "Sphere.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Segment.h"
#include "Plane.h"

/// <summary>
/// �O���錾
/// </summary>
class GameObject;

/// <summary>
/// �����蔻��N���X
/// </summary>
class Collision
{
public:

	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	static bool HitCheck_Sphere_Sphere
	(const  MyCollisionObject::Sphere& sphere, const  MyCollisionObject::Sphere& sphere2, DirectX::SimpleMath::Vector3& hitPos);

	/// <summary>
	/// �����ƕ��ʂ̓����蔻��
	/// </summary>
	static bool HitCheck_Segment_Plane
	(const MyCollisionObject::Segment& segment, const MyCollisionObject::Plane& plane, DirectX::SimpleMath::Vector3& hitPos);

	/// <summary>
	/// �����Ƌ��̓����蔻��
	/// </summary>
	static bool HitCheck_Segment_Sphere
	(const MyCollisionObject::Segment& segment, const MyCollisionObject::Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos);
	
	/// <summary>
	/// �����ƎO�p�`�̓����蔻��
	/// </summary>
	static bool HitCheck_Segment_Triangle
	(const MyCollisionObject::Segment& segment, const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);

	// �O�p�`�̔C�ӂ̓_���O�p�`���ɑ��݂��邩�ǂ���
	static bool Triangle_CheckInner(const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& point);

	// ���ƕ��ʂ̓����蔻��
	static bool HitCheck_Sphere_Plane
	(const MyCollisionObject::Sphere& sphere, const MyCollisionObject::Plane& plane, DirectX::SimpleMath::Vector3& hitPos);

	// ���ƎO�p�`�̏Փ˔���
	static bool HitCheck_Sphere_Triangle
	(const MyCollisionObject::Sphere& sphere, const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);


	/// <summary>
	/// ���ʂ̕�����
	/// </summary>
	/// <param name="plane">����</param>
	/// <param name="p">�_</param>
	/// <returns>���ʂƓ_�̋���</returns>
	static float Plane_Length(const MyCollisionObject::Plane& plane, const DirectX::SimpleMath::Vector3& p)
	{
		float l;
		l = plane.a * p.x + plane.b * p.y + plane.c * p.z + plane.d;
		return l;
	}

public:
	Collision();
	~Collision();
};

