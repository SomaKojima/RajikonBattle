#include "../../pch.h"
#include <list>
#include "PlayerController.h"
#include "../../MouseCursor/MouseCurosrManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerController::PlayerController()
	:
	m_isStop(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerController::~PlayerController()
{
}

/// <summary>
/// �X�V����
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
/// ��]
/// </summary>
void PlayerController::Rotation()
{
	MouseCursorManager& mcm = MouseCursorManager::GetInstace();
	// �ړ��ʂ��擾
	Vector2 moveVec = mcm.GetMoveVec();
	// �ړ��ʂ̒���
	moveVec *= 0.1f;

	// ----- �v���C���[�̉�] -----
	Vector3 up = Vector3::Transform(Vector3::Up, m_gameObject->GetTransform().WorldDir());
	float radian = -XMConvertToRadians(moveVec.x);
	if (moveVec.x != 0)
	{
		// �v���C���[�̌�����ς���
		Quaternion dir = m_gameObject->GetTransform().WorldDir() * Quaternion::CreateFromAxisAngle(up, radian);
		m_gameObject->GetTransform().WorldDir(dir);
	}
}
