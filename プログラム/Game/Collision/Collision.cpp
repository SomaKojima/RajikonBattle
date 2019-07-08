/// <summary>
/// Collision.cpp
/// 
/// 制作日:2018/7/12
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "../Object/GameObject.h"
#include "Collision.h"
#include "../../DebugString.h"

/// <summary>
/// 名前空間
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

	// 中心間の距離の平方を計算f
	DirectX::SimpleMath::Vector3 d = sphere.center - sphere2.center;
	float dist2 = d.Dot(d);

	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
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

	// 線分始点と平面の距離を計算
	float length = Plane_Length(plane, segment.pos);

	// 線分ベクトルの長さの2乗を計算
	float vec_length = segment.vec.Dot(segment.vec);
	// 絶対に届かない場合は終了
	if (vec_length < (length * length)) return false;
	// 線分ベクトルの正規化する
	float vec_length_nomalize = sqrtf(vec_length);
	// cosθを内積を利用して求める
	Vector3 vec = segment.vec * (1.0f / vec_length_nomalize);
	float cos_theta = vec.Dot(Vector3(-plane.a, -plane.b, -plane.c));
	// 線分が平面に届く距離を計算
	float plane_vec_length = length / cos_theta;
	// 届いていない
	if (plane_vec_length > vec_length_nomalize) return false;
	// 交点を計算
	if (&hitPos)
	{
		hitPos = segment.pos + (vec * plane_vec_length);
	}
	return true;
}

bool Collision::HitCheck_Segment_Sphere(const MyCollisionObject::Segment & segment, const MyCollisionObject::Sphere & sphere, Vector3& hitPos)
{
	if (!&segment || !&sphere) return false;

	// (2次方程式) = at^2 + bt + c = 0;
	// 2次方程式におけるa,b,cを計算
	float xa = segment.pos.x - sphere.center.x;
	float ya = segment.pos.y - sphere.center.y;
	float za = segment.pos.z - sphere.center.z;

	// vec = 線分の速度

	// (a) = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	float a = segment.vec.x * segment.vec.x + segment.vec.y * segment.vec.y + segment.vec.z * segment.vec.z;
	// (b) = 2(vec.x * xa + vec.y * ya * vec.z * za);
	float b = 2.0f * (segment.vec.x * xa + segment.vec.y * ya + segment.vec.z * za);
	// (c) = xa^2 + ya^2 + za^2 - radius^2;
	float c = xa * xa + ya * ya + za * za - sphere.radius * sphere.radius;

	// 2次方程式が解けないと判断したときは衝突していないとみなす
	float d = b * b - 4.0f * a * c;
	if (d < 0.0f) return false;

	// 解の公式を解く
	d = sqrtf(d);
	float t0 = (-b + d) / (2.0f * a);
	float t1 = (-b - d) / (2.0f * a);

	float t = 2.0f;
	if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t)) t = t0;
	if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t)) t = t1;

	if (t > 1.0f) return false;

	// 交点を計算
	if (&hitPos)
	{
		hitPos = segment.pos + (segment.vec * t);
	}
	return true;
}

bool Collision::HitCheck_Segment_Triangle(const MyCollisionObject::Segment & segment, const MyCollisionObject::Triangle & triangle, Vector3& hitPos)
{
	if (!&segment || !&triangle) return false;

	// 三角形の平面とチェック
	Vector3 tmp_hit_pos;
	if (!HitCheck_Segment_Plane(segment, triangle.plane, tmp_hit_pos)) return false;
	if (!Triangle_CheckInner(triangle, tmp_hit_pos))
	{
		// 外部
		return false;
	}
	else
	{
		// 内部
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


	//内積で順方向か逆方向か調べる
	double dot_12 = c1.Dot(c2);
	double dot_13 = c1.Dot(c3);

	if (dot_12 >= 0 && dot_13 >= 0) {
		//三角形の内側に点がある
		return true;
	}
	return false;
}

bool Collision::HitCheck_Sphere_Plane(const MyCollisionObject::Sphere & sphere, const MyCollisionObject::Plane & plane, Vector3& hitPos)
{
	if (!&sphere || !&plane) return false;

	float length = Plane_Length(plane, sphere.center);
	if (length > sphere.radius) return false;
	
	// 交点を計算
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

	// 三角形の辺の当たり判定
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

	// 球が三角形の中央にめり込むかどうか
	vec = Vector3(-triangle.plane.a * sphere.radius, -triangle.plane.b * sphere.radius, -triangle.plane.c * sphere.radius);
	segment.Set_Segment(Vector3(sphere.center), Vector3(vec));
	if (HitCheck_Segment_Triangle(segment, triangle, hitPos))
	{
		return true;
	}

	return false;
}