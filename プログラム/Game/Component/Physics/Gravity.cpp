#include "../../../pch.h"
#include "Gravity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Gravity::Gravity()
	:
	m_isHit(false),
	m_gravity(9.8f),
	m_dir(Vector3::Down)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Gravity::~Gravity()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void Gravity::Update(float elapsedTime)
{
	//float g = m_gravity / (60 * 60);
	// オブジェクトの下方向を計算
	Vector3 down = Vector3::Transform(Vector3::Down, m_gameObject->GetTransform().WorldDir());
	// 重力加速度を計算
	Vector3 accel = down * 0.02f;

	// オブジェクトの加速度に加える
	accel += m_gameObject->GetTransform().WorldAccel();
	m_gameObject->GetTransform().WorldAccel(accel);
}

void Gravity::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	
}