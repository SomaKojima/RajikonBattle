/// <summary>
/// Collision.h
/// 
/// 制作日:2018/7/12
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <list>
#include "Sphere.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Segment.h"
#include "Plane.h"

/// <summary>
/// 前方宣言
/// </summary>
class GameObject;

/// <summary>
/// 当たり判定クラス
/// </summary>
class Collision
{
public:

	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	static bool HitCheck_Sphere_Sphere
	(const  MyCollisionObject::Sphere& sphere, const  MyCollisionObject::Sphere& sphere2, DirectX::SimpleMath::Vector3& hitPos);

	/// <summary>
	/// 線分と平面の当たり判定
	/// </summary>
	static bool HitCheck_Segment_Plane
	(const MyCollisionObject::Segment& segment, const MyCollisionObject::Plane& plane, DirectX::SimpleMath::Vector3& hitPos);

	/// <summary>
	/// 線分と球の当たり判定
	/// </summary>
	static bool HitCheck_Segment_Sphere
	(const MyCollisionObject::Segment& segment, const MyCollisionObject::Sphere& sphere, DirectX::SimpleMath::Vector3& hitPos);
	
	/// <summary>
	/// 線分と三角形の当たり判定
	/// </summary>
	static bool HitCheck_Segment_Triangle
	(const MyCollisionObject::Segment& segment, const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);

	// 三角形の任意の点が三角形内に存在するかどうか
	static bool Triangle_CheckInner(const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& point);

	// 球と平面の当たり判定
	static bool HitCheck_Sphere_Plane
	(const MyCollisionObject::Sphere& sphere, const MyCollisionObject::Plane& plane, DirectX::SimpleMath::Vector3& hitPos);

	// 球と三角形の衝突判定
	static bool HitCheck_Sphere_Triangle
	(const MyCollisionObject::Sphere& sphere, const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);


	/// <summary>
	/// 平面の方程式
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="p">点</param>
	/// <returns>平面と点の距離</returns>
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

