#include "../../pch.h"
#include "EnemyControllerr.h"
#include "../../Object/Transform.h"
#include "../../Object/EnemyBullet/EnemyBullet.h"
#include "../../Scene/SceneManager.h"

using namespace DirectX::SimpleMath;

const float EnemyController::ENEMY_SPEED = 0.01f;
const float EnemyController::ENEMY_LEFT_ROTATION = 0.1f; 
const float EnemyController::ENEMY_EYE_RANGE = 90.0f;
const float EnemyController::ENEMY_SHOT_SPEED = 2.0f;
const float EnemyController::ENEMY_SHOT_TIME = 0.5f;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyController::EnemyController(Transform* target)
	:
	m_target(target),
	m_eyeRange(DirectX::XMConvertToRadians(ENEMY_EYE_RANGE)),
	m_shotTime(0.0f),
	m_isStop(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyController::~EnemyController()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void EnemyController::Update(float elapsedTime)
{
	if (m_isStop) return;
	Vector3 up = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	Vector3 up_target = Vector3::Transform(Vector3::Up, m_target->WorldDir());

	float cosine = up.Dot(up_target);
	// ターゲットの上方向と自身の上方向が90度より小さい場合
	if (cosine > 0  && IsInEyeRange() && m_target)
	{
		// 常にプレイヤーの方向を向き、追いかける
		RotationToTarget();
		// 弾を撃つ
		Shot();
	}
	else
	{
		// 左回転
		RotationLeft();
	}
	// 前進
	Addvance();

	m_shotTime += elapsedTime;
}

/// <summary>
/// 視界内に入ったかどうか
/// </summary>
/// <returns></returns>
bool EnemyController::IsInEyeRange()
{
	if (!m_target) return false;

	Transform& transform = m_gameObject->GetTransform();
	Vector3 vec = m_target->WorldPos() - transform.WorldPos();
	Vector3 vec_normallize = vec;
	vec_normallize.Normalize();

	Vector3 forward = Vector3::Transform(Vector3::Forward, transform.WorldDir());

	float cosine = vec_normallize.Dot(forward);
	float radian = acos(cosine);

	if (radian < m_eyeRange)
	{
		return true;
	}
	return false;
}

/// <summary>
/// ターゲットへ方向を向ける
/// </summary>
void EnemyController::RotationToTarget()
{
	if (!m_target) return;

	Transform& transform = m_gameObject->GetTransform();
	Vector3 vec = m_target->WorldPos() - transform.WorldPos();
	Vector3 vec_normallize = vec;
	vec_normallize.Normalize();

	Quaternion inv = Quaternion::Identity;
	transform.WorldDir().Inverse(inv);

	Vector3 vec_local = Vector3::Transform(vec, inv);
	
	// y軸を計算しない
	vec_local.y = 0.0f;

	Vector3 vec_xz = Vector3::Transform(vec_local, transform.WorldDir());

	Vector3 forward = Vector3::Transform(Vector3::Forward, transform.WorldDir());
	Vector3 vec_xz_normalize = vec_xz;
	vec_xz_normalize.Normalize();

	float cosine = forward.Dot(vec_xz_normalize);
	float radian = acos(cosine);
	Vector3 axis = forward.Cross(vec_xz_normalize);

	if (axis != Vector3::Zero)
	{
		Quaternion q = transform.WorldDir() * Quaternion::CreateFromAxisAngle(axis, radian);
		transform.WorldDir(q);
	}
}

void EnemyController::RotationLeft()
{
	Transform& transform = m_gameObject->GetTransform();
	Vector3 up = Vector3::Transform(Vector3::Up, transform.WorldDir());
	Quaternion q = transform.WorldDir() * Quaternion::CreateFromAxisAngle(up, DirectX::XMConvertToRadians(ENEMY_LEFT_ROTATION));
	transform.WorldDir(q);
}

/// <summary>
/// 前進
/// </summary>
void EnemyController::Addvance()
{
	Transform& transform = m_gameObject->GetTransform();
	Vector3 forward = Vector3::Transform(Vector3::Forward, transform.WorldDir());
	float speed = ENEMY_SPEED;

	Vector3 accel = transform.WorldAccel() +  forward * speed;
	transform.WorldAccel(accel);
}

/// <summary>
/// 弾を撃つ
/// </summary>
void EnemyController::Shot()
{
	if ((m_shotTime / ENEMY_SHOT_TIME) < 1.0f) return;
	m_shotTime = 0;

	float speed = -ENEMY_SHOT_SPEED;
	// 弾の作成
	GameObject* bullet = new EnemyBullet();
	bullet->Instance();
	bullet->GetTransform().WorldPos(m_gameObject->GetTransform().WorldPos());
	bullet->GetTransform().WorldVel(Vector3::Transform(Vector3(0, 0, speed), m_gameObject->GetTransform().WorldDir()));

	//　オブジェクトを追加
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.GetGameObjectList().Add(bullet);
}
