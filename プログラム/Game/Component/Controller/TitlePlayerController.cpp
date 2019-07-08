#include "../../pch.h"
#include "TitlePlayerController.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
TitlePlayerController::TitlePlayerController()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitlePlayerController::~TitlePlayerController()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void TitlePlayerController::Update(float elapsedTime)
{
	// 移動
	Move();
	// 回転
	Rotation();
}

/// <summary>
/// 回転
/// </summary>
void TitlePlayerController::Rotation()
{
	float angle = 1.5f;
	Vector3 up = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	Quaternion q = m_gameObject->GetTransform().WorldDir() * Quaternion::CreateFromAxisAngle(up, XMConvertToRadians(angle));
	m_gameObject->GetTransform().WorldDir(q);
}

/// <summary>
/// 移動
/// </summary>
void TitlePlayerController::Move()
{
	Vector3 forward = Vector3::Transform(Vector3::Forward, m_gameObject->GetTransform().WorldDir());
	float speed = 0.002f;
	Vector3 accel = m_gameObject->GetTransform().WorldAccel() + forward * speed;
	m_gameObject->GetTransform().WorldAccel(accel);
}
