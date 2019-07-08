/// <summary>
/// �C���N���[�h
/// </summary>
#include "../../pch.h"
#include "MouseCurosrManager.h"
#include "../SubGame.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
MouseCursorManager::MouseCursorManager()
	:
	m_isVisible(true),
	m_undoIsVisible(-1),
	m_isMove(true),
	m_undoIsMove(-1),
	m_moveVec(Vector2::Zero)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MouseCursorManager::~MouseCursorManager()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void MouseCursorManager::Update(float elapsedTime)
{
	if (GetActiveWindow() || !GetIsMove())
	{
		// ----- �E�B���h�E�̒����`(Rectangle)�̏����擾����
		RECT wRect;
		GetWindowRect(GetActiveWindow(), &wRect);
		int width = (wRect.right - wRect.left);
		int height = (wRect.bottom - wRect.top);

		// ----- �E�B���h�E�̒��S���W���擾���� -----
		int centerX = wRect.left + (width / 2);
		int centerY = wRect.top + (height / 2);

		// ----- �}�E�X�̍��W���擾���� -----
		POINT p;
		GetCursorPos(&p);

		// ----- �}�E�X�̈ړ��ʂ��擾���� -----
		m_moveVec = Vector2((float)(p.x - centerX), (float)(p.y - centerY));
	}

	if (!m_isMove)
	{
		MoveCenter();
	}

	if (m_isVisible)
	{
		// �}�E�X�̕\��
		while (ShowCursor(TRUE) < 0);
	}
	else
	{
		// �}�E�X�̔�\��
		while (ShowCursor(FALSE) >= 0);
	}
}

/// <summary>
/// ������ς���
/// </summary>
/// <param name="isVisible"></param>
void MouseCursorManager::ChangeVisible(bool isVisible, bool isDebug)
{
	if (isDebug) 
	{
		m_undoIsVisible = m_isVisible;
	}
	if (m_undoIsVisible == -1) m_undoIsVisible = isVisible;

	m_isVisible = isVisible;
}
/// <summary>
/// ������ς���
/// </summary>
/// <param name="isMove"></param>
void MouseCursorManager::ChangeMoveMode(bool isMove, bool isDebug)
{
	if (isDebug)
	{
		m_undoIsMove = m_isMove;
	}
	if (m_undoIsMove == -1) m_undoIsMove = isMove;

	m_isMove = isMove;
}

/// <summary>
/// �}�E�X�J�[�\������ʒ����Ɉړ�������
/// </summary>
void MouseCursorManager::MoveCenter()
{
	// ----- �E�B���h�E�̏�񂪎擾�ł��Ȃ��ꍇ -----
	if (!GetActiveWindow()) return;

	// ���g�E�B���h�E���A�N�e�B�u���ǂ����𔻒�
	SubGame& subGame = SubGame::GetInstace();
	if (GetActiveWindow() != subGame.GetWindow()) return;

	// ----- �E�B���h�E�̒����`(Rectangle)�̏����擾����
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int width = (wRect.right - wRect.left) / 2;
	int height = (wRect.bottom - wRect.top) / 2;

	// ----- �E�B���h�E�̒��S���W���擾���� -----
	int centralX = wRect.left + width;
	int centralY = wRect.top + height;
	// ----- �}�E�X�̍��W���E�B���h�E�̒����ɌŒ肷�� -----
	SetCursorPos(centralX, centralY);
}

/// <summary>
/// �ЂƂO�ɖ߂�
/// </summary>
void MouseCursorManager::Undo()
{
	if(m_undoIsMove != -1) m_isMove = (bool)m_undoIsMove;
	if(m_undoIsVisible != -1) m_isVisible = (bool)m_undoIsVisible;
}

DirectX::SimpleMath::Vector2 MouseCursorManager::GetPos()
{
	// ���݂̃J�[�\���̈ʒu���擾
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(GetActiveWindow(), &point);

	return Vector2(point.x, point.y);

}
