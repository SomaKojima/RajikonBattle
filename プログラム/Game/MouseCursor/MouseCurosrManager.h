#pragma once
#include "../Utility/Singleton.h"

class MouseCursorManager : public Singleton<MouseCursorManager>
{
public:
	MouseCursorManager();
	~MouseCursorManager();

public:
	// 更新処理
	void Update(float elapsedTime);
	// 可視化を変える
	void ChangeVisible(bool isVisible, bool isDebug = false);
	// 動きを変える
	void ChangeMoveMode(bool isMove, bool isDebug = false);
	// マウスカーソルを画面中央に移動させる
	void MoveCenter();
	// ひとつ前に戻る
	void Undo();

	bool GetIsVisible() { return m_isVisible; }
	bool GetIsMove() { return m_isMove; }
	// マウスの移動量を取得
	DirectX::SimpleMath::Vector2 GetMoveVec() { return m_moveVec; }
	// マウスの座標
	DirectX::SimpleMath::Vector2 GetPos();

private:
	bool m_isVisible;
	int m_undoIsVisible;
	bool m_isMove;
	int m_undoIsMove;
	DirectX::SimpleMath::Vector2 m_moveVec;
};