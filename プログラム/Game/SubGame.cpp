#include "../pch.h"
#include "SubGame.h"
#include "../Game.h"

#include "Utility/InputManager.h"
#include "Scene/SceneManager.h"
#include "Collision/CCell.h"
#include "Collision/CollisionManager.h"
#include "MouseCursor/MouseCurosrManager.h"
#include "Data/Texture/TextureData.h"

#include "../../DebugString.h"

SubGame::SubGame()
	:
	m_game(nullptr),
	m_isStop(false)
{
}

SubGame::~SubGame()
{
	m_game = nullptr;
}

void SubGame::Initialize(Game* game)
{
	// ゲームの設定
	m_game = game;

	// 当たり判定の管理の初期化
	CollisionManager& collisionManager = CollisionManager::GetInstace();
	collisionManager.Initialize();

	// 当たり判定の空間を作成
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	CellRoomInfo room{ -500.0f, -500.0f, -500.0f, 500.0f, 500.0f, 500.0f };
	cLiner8TreeManager.Init(3, room);
	cLiner8TreeManager.InitCollisionMatrix();

	// シーン管理の初期化
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.ChangeSceneID(SceneManager::SceneID::Logo);
#ifdef _DEBUG
	sceneManager.ChangeSceneID(SceneManager::SceneID::Title);
#endif
	sceneManager.Initialize();
}

void SubGame::Update(float elapsedTime)
{
	// 入力の更新
	InputManager& inputManager = InputManager::GetInstace();
	inputManager.Update(elapsedTime);
	// マウスカーソルの管理を初期化
	MouseCursorManager& mouseCursorManager = MouseCursorManager::GetInstace();

	SceneManager& sceneManager = SceneManager::GetInstace();

	// デバッグの文字を取得
	DebugString& debugString = DebugString::GetInstace();

#ifdef _DEBUG
	// 一時停止する
	if (inputManager.GetKeyboardTracker().pressed.P)
	{
		m_isStop = !m_isStop;
		if (m_isStop)
		{
			mouseCursorManager.ChangeMoveMode(m_isStop, true);
			mouseCursorManager.ChangeVisible(m_isStop, true);
		}
		else
		{
			mouseCursorManager.Undo();
		}
		mouseCursorManager.MoveCenter();
		if(m_isStop) debugString.SetState(DebugString::STATE::STOP);
		else debugString.SetState(DebugString::STATE::PLAY);
	}

	// リセットする
	if (inputManager.GetKeyboardTracker().pressed.O)
	{
		debugString.Reset();
		sceneManager.Reset();
		mouseCursorManager.MoveCenter();
		// 停止中の場合
		if (m_isStop)
		{
			mouseCursorManager.ChangeMoveMode(m_isStop, true);
			mouseCursorManager.ChangeVisible(m_isStop, true);
		}
	}

	// タイトルに移動する
	if (inputManager.GetKeyboardTracker().pressed.I)
	{
		sceneManager.ChangeSceneID(SceneManager::SceneID::Logo);
	}

#endif

	// 停止中は処理しない
	if (!m_isStop)
	{
		// 当たり判定の処理
		CollisionManager& collisionManager = CollisionManager::GetInstace();
		//collisionManager.Update(elapsedTime);

		//// 当たり判定の空間を作成
		CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
		cLiner8TreeManager.HitCheck();

		// シーンの更新
		sceneManager.Update(elapsedTime);
	}

	// マウスカーソル管理を更新
	mouseCursorManager.Update(elapsedTime);
}

void SubGame::Renderer()
{
	// シーンの描画
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Render();
}

void SubGame::Finalize()
{

	// シーンの描画
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Finalize();
}
