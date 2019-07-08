#include "../../pch.h"
#include "PlayCamera.h"
#include "Mouse.h"
#include "../Object/GameObject.h"
#include "CameraManager.h"
#include "../MouseCursor/MouseCurosrManager.h"
#include "../../DebugString.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayCamera::PlayCamera(GameObject* target)
	:
	m_target(target),
	m_y(0),
	m_rotation(0.0f),
	m_type(CAMERA_TYPE::PLAY)
{
}

void PlayCamera::Initialize()
{
	// ----- カメラの座標を求める -----
	Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 0.0f, -10.0f), m_target->GetTransform().WorldDir()) +
		Vector3::Transform(Vector3(0.0f, 2.0f * cos(m_y), 2.0f * sin(m_y)), m_target->GetTransform().WorldDir());
	Vector3 eyePos = m_target->GetTransform().WorldPos() + eyeVec;
	Vector3 target = m_target->GetTransform().WorldPos() + Vector3::Transform(Vector3(0.0f, 0.0f, 10.0f), m_target->GetTransform().WorldDir());

	SetPositionTarget(eyePos, target);
}

void PlayCamera::Update(float elapsedTime)
{
	switch (m_type)
	{
	case PlayCamera::PLAY:
		PlayScene(elapsedTime);
		break;
	case PlayCamera::RESULT:
		ResultScene(elapsedTime);
		break;
	}
}

void PlayCamera::PlayScene(float elapsedTime)
{
	
	MouseCursorManager& mcm = MouseCursorManager::GetInstace();
	Transform& transform = m_gameObject->GetTransform();
	Transform& target = m_target->GetTransform();

	Vector2 mouseVec = mcm.GetMoveVec();
	// 移動量の調整
	mouseVec *= 0.1f;


	// ----- 回転を更新 -----
	m_y += XMConvertToRadians(mouseVec.y);

	// 回転の制限
	float maxRange = 80.0f;
	if (m_y > XMConvertToRadians(maxRange))
	{
		m_y = XMConvertToRadians(maxRange);
	}
	else if (m_y < -XMConvertToRadians(maxRange))
	{
		m_y = -XMConvertToRadians(maxRange);
	}

	// ----- カメラの向きを設定する -----
	Vector3 axis = Vector3::Transform(Vector3::Right, target.WorldDir());
	Quaternion q = Quaternion::CreateFromAxisAngle(axis, -m_y);
	Quaternion from = transform.WorldDir();
	Quaternion to = target.WorldDir() * q;
	Quaternion cameraDir = Quaternion::Lerp(from, to, 0.3f);
	transform.WorldDir(cameraDir);

	// ----- カメラの座標を求める -----
	Vector3 posFrom = transform.WorldPos();
	Vector3 posTo = target.WorldPos() + Vector3::Transform(Vector3(0.0f, 3.0f, 10.0f), transform.WorldDir());
	Vector3 eyePos = Vector3::Lerp(posFrom, posTo, 0.5f);
	transform.WorldPos(eyePos);


	// ----- カメラの注視点を求める -----
	Vector3 targetPos = target.WorldPos() + Vector3::Transform(Vector3(0.0f, 0.0f, -10.0f), transform.WorldDir());


	// ----- カメラの上方向を求める -----
	Vector3 up = Vector3::Transform(Vector3::Up, transform.WorldDir());

	// カメラ管理のビューを更新する
	CameraManager& cameraManager = CameraManager::GetInstace();
	cameraManager.SetView(Matrix::CreateLookAt(eyePos, targetPos, up));
}

void PlayCamera::ResultScene(float elapsedTime)
{
	Transform& transform = m_gameObject->GetTransform();
	// カメラの座標を計算
	Vector3 eyePos = Vector3::Transform(Vector3(0.0f, 10.0f, 20.0f), Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(m_rotation)));
	eyePos = m_target->GetTransform().WorldPos() + Vector3::Transform(eyePos, m_target->GetTransform().WorldDir());
	eyePos = Vector3::Lerp(transform.WorldPos(), eyePos, 0.1f);
	transform.WorldPos(eyePos);

	// カメラの注視点
	Vector3 targetPos = m_target->GetTransform().WorldPos();

	Vector3 up = Vector3::Transform(Vector3::Up, m_target->GetTransform().WorldDir());
	// カメラ管理のビューを更新する
	CameraManager& cameraManager = CameraManager::GetInstace();
	cameraManager.SetView(Matrix::CreateLookAt(eyePos, targetPos, up));

	m_rotation += 0.5f;
}

