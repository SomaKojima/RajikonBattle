/// <summary>
/// インクルード
/// </summary>
#include "../../pch.h"
#include "MouseCurosrManager.h"
#include "../SubGame.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
MouseCursorManager::~MouseCursorManager()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void MouseCursorManager::Update(float elapsedTime)
{
	if (GetActiveWindow() || !GetIsMove())
	{
		// ----- ウィンドウの長方形(Rectangle)の情報を取得する
		RECT wRect;
		GetWindowRect(GetActiveWindow(), &wRect);
		int width = (wRect.right - wRect.left);
		int height = (wRect.bottom - wRect.top);

		// ----- ウィンドウの中心座標を取得する -----
		int centerX = wRect.left + (width / 2);
		int centerY = wRect.top + (height / 2);

		// ----- マウスの座標を取得する -----
		POINT p;
		GetCursorPos(&p);

		// ----- マウスの移動量を取得する -----
		m_moveVec = Vector2((float)(p.x - centerX), (float)(p.y - centerY));
	}

	if (!m_isMove)
	{
		MoveCenter();
	}

	if (m_isVisible)
	{
		// マウスの表示
		while (ShowCursor(TRUE) < 0);
	}
	else
	{
		// マウスの非表示
		while (ShowCursor(FALSE) >= 0);
	}
}

/// <summary>
/// 可視化を変える
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
/// 動きを変える
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
/// マウスカーソルを画面中央に移動させる
/// </summary>
void MouseCursorManager::MoveCenter()
{
	// ----- ウィンドウの情報が取得できない場合 -----
	if (!GetActiveWindow()) return;

	// 自身ウィンドウがアクティブ化どうかを判定
	SubGame& subGame = SubGame::GetInstace();
	if (GetActiveWindow() != subGame.GetWindow()) return;

	// ----- ウィンドウの長方形(Rectangle)の情報を取得する
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int width = (wRect.right - wRect.left) / 2;
	int height = (wRect.bottom - wRect.top) / 2;

	// ----- ウィンドウの中心座標を取得する -----
	int centralX = wRect.left + width;
	int centralY = wRect.top + height;
	// ----- マウスの座標をウィンドウの中央に固定する -----
	SetCursorPos(centralX, centralY);
}

/// <summary>
/// ひとつ前に戻る
/// </summary>
void MouseCursorManager::Undo()
{
	if(m_undoIsMove != -1) m_isMove = (bool)m_undoIsMove;
	if(m_undoIsVisible != -1) m_isVisible = (bool)m_undoIsVisible;
}

DirectX::SimpleMath::Vector2 MouseCursorManager::GetPos()
{
	// 現在のカーソルの位置を取得
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(GetActiveWindow(), &point);

	return Vector2(point.x, point.y);

}
