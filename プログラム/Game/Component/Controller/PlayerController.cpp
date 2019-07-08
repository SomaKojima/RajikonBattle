#include "../../pch.h"
#include <list>
#include "PlayerController.h"
#include "../../MouseCursor/MouseCurosrManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerController::PlayerController()
	:
	m_isStop(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerController::~PlayerController()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void PlayerController::Update(float elapsedTime)
{
	if (m_isStop) return;
	 list<ICommand*> commandVec = inputHnadler.GetInputHnadle(elapsedTime);
	 for (auto ite = commandVec.begin(); ite != commandVec.end(); ite++)
	 {
		 if (!(*ite))continue;
		 (*ite)->Excute(*m_gameObject);
	 }
	 Rotation();
}

/// <summary>
/// 回転
/// </summary>
void PlayerController::Rotation()
{
	MouseCursorManager& mcm = MouseCursorManager::GetInstace();
	// 移動量を取得
	Vector2 moveVec = mcm.GetMoveVec();
	// 移動量の調整
	moveVec *= 0.1f;

	// ----- プレイヤーの回転 -----
	Vector3 up = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	float radian = -XMConvertToRadians(moveVec.x);
	if (moveVec.x != 0)
	{
		// プレイヤーの向きを変える
		Quaternion dir = m_gameObject->GetTransform().WorldDir() * Quaternion::CreateFromAxisAngle(up, radian);
		m_gameObject->GetTransform().WorldDir(dir);
	}
}
