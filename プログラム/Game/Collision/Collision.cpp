/// <summary>
/// Collision.cpp
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "../Object/GameObject.h"
#include "Collision.h"
#include "../../DebugString.h"

/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX::SimpleMath;

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::HitCheck_Sphere_Sphere(const MyCollisionObject::Sphere& sphere, const MyCollisionObject::Sphere& sphere2, Vector3& hitPos)
{
	if (!&sphere || !&sphere2) return false;

	// ���S�Ԃ̋����̕������v�Zf
	DirectX::SimpleMath::Vector3 d = sphere.center - sphere2.center;
	float dist2 = d.Dot(d);

	// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
	float radiusSum = sphere.radius + sphere2.radius;
	if (dist2 <= radiusSum * radiusSum)
	{
		if (&hitPos)
		{
			float l = (sphere.radius + sphere2.radius) / 2;
			d.Normalize();
			hitPos = sphere2.center + (d * l);
		}
		return true;
	}
	return false;
}

bool Collision::HitCheck_Segment_Plane(const MyCollisionObject::Segment & segment, const MyCollisionObject::Plane & plane, Vector3& hitPos)
{
	if (!&segment || !&plane) return false;

	// �����n�_�ƕ��ʂ̋������v�Z
	float length = Plane_Length(plane, segment.pos);

	// �����x�N�g���̒�����2����v�Z
	float vec_length = segment.vec.Dot(segment.vec);
	// ��΂ɓ͂��Ȃ��ꍇ�͏I��
	if (vec_length < (length * length)) return false;
	// �����x�N�g���̐��K������
	float vec_length_nomalize = sqrtf(vec_length);
	// cos�Ƃ���ς𗘗p���ċ��߂�
	Vector3 vec = segment.vec * (1.0f / vec_length_nomalize);
	float cos_theta = vec.Dot(Vector3(-plane.a, -plane.b, -plane.c));
	// ���������ʂɓ͂��������v�Z
	float plane_vec_length = length / cos_theta;
	// �͂��Ă��Ȃ�
	if (plane_vec_length > vec_length_nomalize) return false;
	// ��_���v�Z
	if (&hitPos)
	{
		hitPos = segment.pos + (vec * plane_vec_length);
	}
	return true;
}

bool Collision::HitCheck_Segment_Sphere(const MyCollisionObject::Segment & segment, const MyCollisionObject::Sphere & sphere, Vector3& hitPos)
{
	if (!&segment || !&sphere) return false;

	// (2��������) = at^2 + bt + c = 0;
	// 2���������ɂ�����a,b,c���v�Z
	float xa = segment.pos.x - sphere.center.x;
	float ya = segment.pos.y - sphere.center.y;
	float za = segment.pos.z - sphere.center.z;

	// vec = �����̑��x

	// (a) = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	float a = segment.vec.x * segment.vec.x + segment.vec.y * segment.vec.y + segment.vec.z * segment.vec.z;
	// (b) = 2(vec.x * xa + vec.y * ya * vec.z * za);
	float b = 2.0f * (segment.vec.x * xa + segment.vec.y * ya + segment.vec.z * za);
	// (c) = xa^2 + ya^2 + za^2 - radius^2;
	float c = xa * xa + ya * ya + za * za - sphere.radius * sphere.radius;

	// 2���������������Ȃ��Ɣ��f�����Ƃ��͏Փ˂��Ă��Ȃ��Ƃ݂Ȃ�
	float d = b * b - 4.0f * a * c;
	if (d < 0.0f) return false;

	// ���̌���������
	d = sqrtf(d);
	float t0 = (-b + d) / (2.0f * a);
	float t1 = (-b - d) / (2.0f * a);

	float t = 2.0f;
	if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t)) t = t0;
	if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t)) t = t1;

	if (t > 1.0f) return false;

	// ��_���v�Z
	if (&hitPos)
	{
		hitPos = segment.pos + (segment.vec * t);
	}
	return true;
}

bool Collision::HitCheck_Segment_Triangle(const MyCollisionObject::Segment & segment, const MyCollisionObject::Triangle & triangle, Vector3& hitPos)
{
	if (!&segment || !&triangle) return false;

	// �O�p�`�̕��ʂƃ`�F�b�N
	Vector3 tmp_hit_pos;
	if (!HitCheck_Segment_Plane(segment, triangle.plane, tmp_hit_pos)) return false;
	if (!Triangle_CheckInner(triangle, tmp_hit_pos))
	{
		// �O��
		return false;
	}
	else
	{
		// ����
		if (&hitPos)
		{
			hitPos = tmp_hit_pos;
		}
		return true;
	}
}

bool Collision::Triangle_CheckInner(const MyCollisionObject::Triangle & triangle, DirectX::SimpleMath::Vector3& point)
{
	if (!&triangle) return false;

	Vector3 AB = triangle.pos[1] - triangle.pos[0];
	Vector3 BP = point - triangle.pos[1];

	Vector3 BC = triangle.pos[2] - triangle.pos[1];
	Vector3 CP = point - triangle.pos[2];

	Vector3 CA = triangle.pos[0] - triangle.pos[2];
	Vector3 AP = point - triangle.pos[0];

	Vector3 c1 = AB.Cross(BP);
	Vector3 c2 = BC.Cross(CP);
	Vector3 c3 = CA.Cross(AP);


	//���ςŏ��������t���������ׂ�
	double dot_12 = c1.Dot(c2);
	double dot_13 = c1.Dot(c3);

	if (dot_12 >= 0 && dot_13 >= 0) {
		//�O�p�`�̓����ɓ_������
		return true;
	}
	return false;
}

bool Collision::HitCheck_Sphere_Plane(const MyCollisionObject::Sphere & sphere, const MyCollisionObject::Plane & plane, Vector3& hitPos)
{
	if (!&sphere || !&plane) return false;

	float length = Plane_Length(plane, sphere.center);
	if (length > sphere.radius) return false;
	
	// ��_���v�Z
	if (&hitPos)
	{
		//length = sphere.radius - length;
		hitPos = sphere.center - Vector3(plane.a, plane.b, plane.c) * length;
	}
	return true;
}

bool Collision::HitCheck_Sphere_Triangle(const MyCollisionObject::Sphere & sphere, const MyCollisionObject::Triangle & triangle, Vector3& hitPos)
{
  	if (!&sphere || !&triangle) return false;

	if (!HitCheck_Sphere_Plane(sphere, triangle.plane, hitPos)) return false;

	// �O�p�`�̕ӂ̓����蔻��
	Vector3 vec;
	vec = triangle.pos[1] - triangle.pos[0];
	MyCollisionObject::Segment segment;
	segment.Set_Segment(Vector3(triangle.pos[0]), Vector3(vec));
	if (HitCheck_Segment_Sphere(segment, sphere, hitPos))
	{
		return true;
	}

	vec = triangle.pos[2] - triangle.pos[1];
	segment.Set_Segment(Vector3(triangle.pos[1]), Vector3(vec));
	if (HitCheck_Segment_Sphere(segment, sphere, hitPos))
	{
		return true;
	}

	vec = triangle.pos[0] - triangle.pos[2];
	segment.Set_Segment(Vector3(triangle.pos[2]), Vector3(vec));
	if (HitCheck_Segment_Sphere(segment, sphere, hitPos))
	{
		return true;
	}

	// �����O�p�`�̒����ɂ߂荞�ނ��ǂ���
	vec = Vector3(-triangle.plane.a * sphere.radius, -triangle.plane.b * sphere.radius, -triangle.plane.c * sphere.radius);
	segment.Set_Segment(Vector3(sphere.center), Vector3(vec));
	if (HitCheck_Segment_Triangle(segment, triangle, hitPos))
	{
		return true;
	}

	return false;
}