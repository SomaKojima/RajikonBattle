/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "CollisionSphere.h"
#include "../../SubGame.h"
#include "../../DebugString.h"
#include "../../Collision/CCell.h"
#include "../../Collision/CollisionManager.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="radius">半径</param>
CollisionSphere::CollisionSphere(DirectX::SimpleMath::Vector3 centerPos, float radius)
	:
	CollisionComponent(new MyCollisionObject::Sphere()),
	m_centerPos(centerPos),
	m_obj(nullptr),
	m_isBound(false)
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	sphere.radius = radius;
}

/// <summary>
/// デストラクタ
/// </summary>
CollisionSphere::~CollisionSphere()
{

}

/// <summary>
/// 初期化
/// </summary>
void CollisionSphere::Initialize()
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	//　座標の更新
	sphere.center = m_gameObject->GetTransform().WorldPos() + m_centerPos;

	m_collisionObject->SetGameObject(*m_gameObject);

	CollisionManager& collisionManager = CollisionManager::GetInstace();
	//collisionManager.Add(*m_collisionObject, m_gameObject->GetTag());
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionSphere::Update(float elapsedTime)
{
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionSphere::LateUpdate(float elapsedTime)
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	//　座標の更新
	sphere.center = m_gameObject->GetTransform().WorldPos() + m_centerPos;
	// 空間登録
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	Vector3 pos = Vector3(sphere.center.x - sphere.radius, sphere.center.y - sphere.radius, sphere.center.z - sphere.radius);
	Vector3 pos2 = Vector3(sphere.center.x + sphere.radius, sphere.center.y + sphere.radius, sphere.center.z + sphere.radius);

	cLiner8TreeManager.Register(*m_collisionObject, pos, pos2);


	// 強制的にマイナスのY軸にはいかないようにする

	// 座標の更新
	pos = m_gameObject->GetTransform().WorldPos();

	MyCollisionObject::Plane plane;
	plane.Set_Plane(Vector3::Up, Vector3::Zero);
	Vector3 normal(0, 1, 0);
	Vector3 hit;
	if (Collision::HitCheck_Sphere_Plane(sphere, plane, hit))
	{
		pos = hit + normal * sphere.radius;
		m_gameObject->GetTransform().WorldPos(pos);
	}
}
	
/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void CollisionSphere::Render()
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	Matrix world = Matrix::CreateTranslation(m_centerPos) * m_gameObject->GetTransform().WorldMatrix();
	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugSphere>(SubGame::GetInstace().GetGame()->GetDevice(), m_centerPos, sphere.radius);
	}
	else
	{
		Game* game = SubGame::GetInstace().GetGame();
		//m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// 終了
/// </summary>
/// <param name="entity">実体</param>
void CollisionSphere::Finalize()
{
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	sphere.Remove();
}

void CollisionSphere::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	// 自身の球のデータ
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;
	switch (collisionObject.type)
	{
		/// <summary>
		/// 球の衝突処理
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_SPHERE:
		{
			// 相手の球のデータ
			MyCollisionObject::Sphere& sphere2 = *collisionObject.shape.sphere;

			// 球の押し出し
			Vector3 dir = sphere.center - sphere2.center;
			dir.Normalize();
			Vector3 pos = hitPos + dir * (sphere.radius + sphere2.radius);
			m_gameObject->GetTransform().WorldPos(pos);
		}
		break;

		/// <summary>
		/// メッシュの衝突処理
		/// </summary>
	case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_MESH:
		{
			// 相手のメッシュのデータ
			MyCollisionObject::Mesh& mesh2 = *collisionObject.shape.mesh;
			for (auto ite = mesh2.triangles.begin(); ite != mesh2.triangles.end(); ite++)
			{
				if ((*ite)->collisionData.isHit)
				{
					// 壁刷り
					HitBack(*(*ite), (*ite)->collisionData.hitPos);
				}
			}
		}
		break;

		/// <summary>
		/// メッシュの衝突処理
		/// </summary>
		case MyCollisionObject::SHAPE_TYPE::SHAPE_TYPE_TRIANGLE:
		{
			// 相手のメッシュのデータ
			MyCollisionObject::Triangle& triangle2 = *collisionObject.shape.triangle;
			if (triangle2.collisionData.isHit)
			{
				// 壁刷り
				HitBack(triangle2, triangle2.collisionData.hitPos);
			}
		}
		break;
	}
}


/// <summary>
/// 壁刷り
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
void CollisionSphere::HitBack(const MyCollisionObject::Triangle & triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// 三角形の法線を取得
	Vector3 normal = Vector3(triangle.plane.a, triangle.plane.b, triangle.plane.c);
	Transform& transform = m_gameObject->GetTransform();
	// 自身の球のデータ
	MyCollisionObject::Sphere& sphere = *m_collisionObject->shape.sphere;

	// 速度で壁刷りを行う
	Vector3 w_vec_vel = WallCulc(normal, transform.WorldVel());
	transform.WorldVel(w_vec_vel);

	// 座標の更新
	Vector3 pos = transform.WorldPos();
	Vector3 hit;
	Collision::HitCheck_Sphere_Plane(sphere, triangle.plane, hit);
	pos = hit + normal * sphere.radius;
	transform.WorldPos(pos);

	// 加速度を壁刷りを行った速度にする
	Vector3 w_vec_accel = WallCulc(normal, transform.WorldAccel());
	transform.WorldAccel(w_vec_accel);
}


/// <summary>
/// 壁刷りの計算
/// </summary>
/// <param name="triangle"></param>
/// <param name="hitPos"></param>
/// <param name="vel"></param>
/// <returns></returns>
Vector3 CollisionSphere::WallCulc(const DirectX::SimpleMath::Vector3& normal, DirectX::SimpleMath::Vector3 vel, bool boundFlag 
)
{
	// 速度を取得
	Vector3 vec = vel;

	float l = -vec.Dot(normal);
	if(l > 0.0f)
	{
		if (boundFlag)
		{
			return (vec + (2 * l * normal));
		}
		else
		{
			return vec + (l * normal);
		}
	}
	return vel;
}

