#pragma once
#include "../Utility/Singleton.h"

class MouseCursorManager : public Singleton<MouseCursorManager>
{
public:
	MouseCursorManager();
	~MouseCursorManager();

public:
	// �X�V����
	void Update(float elapsedTime);
	// ������ς���
	void ChangeVisible(bool isVisible, bool isDebug = false);
	// ������ς���
	void ChangeMoveMode(bool isMove, bool isDebug = false);
	// �}�E�X�J�[�\������ʒ����Ɉړ�������
	void MoveCenter();
	// �ЂƂO�ɖ߂�
	void Undo();

	bool GetIsVisible() { return m_isVisible; }
	bool GetIsMove() { return m_isMove; }
	// �}�E�X�̈ړ��ʂ��擾
	DirectX::SimpleMath::Vector2 GetMoveVec() { return m_moveVec; }
	// �}�E�X�̍��W
	DirectX::SimpleMath::Vector2 GetPos();

private:
	bool m_isVisible;
	int m_undoIsVisible;
	bool m_isMove;
	int m_undoIsMove;
	DirectX::SimpleMath::Vector2 m_moveVec;
};