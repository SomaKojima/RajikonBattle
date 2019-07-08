#include "../../pch.h"
#include "TitlePlayerController.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitlePlayerController::TitlePlayerController()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitlePlayerController::~TitlePlayerController()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void TitlePlayerController::Update(float elapsedTime)
{
	// �ړ�
	Move();
	// ��]
	Rotation();
}

/// <summary>
/// ��]
/// </summary>
void TitlePlayerController::Rotation()
{
	float angle = 1.5f;
	Vector3 up = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	Quaternion q = m_gameObject->GetTransform().WorldDir() * Quaternion::CreateFromAxisAngle(up, XMConvertToRadians(angle));
	m_gameObject->GetTransform().WorldDir(q);
}

/// <summary>
/// �ړ�
/// </summary>
void TitlePlayerController::Move()
{
	Vector3 forward = Vector3::Transform(Vector3::Forward, m_gameObject->GetTransform().WorldDir());
	float speed = 0.002f;
	Vector3 accel = m_gameObject->GetTransform().WorldAccel() + forward * speed;
	m_gameObject->GetTransform().WorldAccel(accel);
}
