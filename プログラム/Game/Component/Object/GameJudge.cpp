#include "../../pch.h"
#include "GameJudge.h"
#include "../../Camera/PlayCamera.h"
#include "../../Object/Car/Player.h"
#include "../../Object/EnemyCar/Enemy.h"
#include "StatusHP.h"
#include "../Controller/PlayerController.h"
#include "../Controller/EnemyControllerr.h"
#include "../Object/TimeCounter.h"
#include "../../Object/ResultStr/ResultStr.h"
#include "../../Scene/SceneManager.h"

const float GameJudge::RESUTL_TO_CHANGE_TIME = 5.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
GameJudge::GameJudge()
	:
	m_isStart(false),
	m_player(nullptr),
	m_playerHP(nullptr),
	m_playerController(nullptr),
	m_enemy(nullptr),
	m_enemyHP(nullptr),
	m_enemyController(nullptr),
	m_camera(nullptr),
	m_timer(nullptr),
	m_isResult(false),
	m_resultTime(0.0f),
	m_a(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameJudge::~GameJudge()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void GameJudge::Update(float elapsedTime)
{
	if (m_isResult)
	{
		m_resultTime += elapsedTime;
		if (m_resultTime > RESUTL_TO_CHANGE_TIME)
		{
			SceneManager& sceneManager = SceneManager::GetInstace();
			sceneManager.ChangeSceneID(SceneManager::SceneID::Title);
		}
		if (!m_a)
		{
			m_a = MyLibrary::ADX2Le::GetInstance();
			m_a->LoadAcb(L"Play.acb", L"Play.awb");
		}
		else if (!MyLibrary::ADX2Le::GetInstance()->IsPlayStateByID(m_id))
		{
			m_id = m_a->Play(1);
		}
	}
	else
	{
		// プレイヤーの体力がない場合
		if (m_playerHP)
		{
			if (m_playerHP->GetHP() <= 0)
			{
				m_player->Delete();
				InitPlayerInfo();
				EnemyWin();
			}
		}

		// 敵の体力がない場合
		if (m_enemyHP)
		{
			if (m_enemyHP->GetHP() <= 0)
			{
				m_enemy->Delete();
				InitEnemyInfo();
				PlayerWin();
			}
		}

		// 制限時間を判定
		if (m_timer)
		{
			if (m_timer->GetTime() <= 0.0f)
			{
				TimeUp();
			}
			if (m_timer->GetStartTime() > 0.0f)
			{
				StartThreeTime();
			}
			else if (!m_isStart)
			{
				Start();
			}
		}

		if (m_isResult)
		{
			ResultStart();
		}
	}
}

/// <summary>
/// プレイヤーが勝った場合の処理
/// </summary>
void GameJudge::PlayerWin()
{
	if (!m_camera || !m_player) return;
	m_camera->SetTarget(m_player);
	m_camera->SetType(PlayCamera::CAMERA_TYPE::RESULT);
	m_isResult = true;

	// 操作を止める
	if (m_playerController)
	{
		m_playerController->SetIsStop(true);
	}

	if (m_timer)
	{
		m_timer->SetIsStop(true);
	}

	// 文字を表示
	ResultStr* resultStr = new ResultStr();
	resultStr->Instance(ResultStr::Type::You);
	resultStr->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 300.0f, 0.0f));
	SceneManager::GetInstace().GetGameObjectList().Add(resultStr);
}

/// <summary>
/// 敵が勝った場合の処理
/// </summary>
void GameJudge::EnemyWin()
{
	if (!m_camera || !m_enemy) return;
	m_camera->SetTarget(m_enemy);
	m_camera->SetType(PlayCamera::CAMERA_TYPE::RESULT);
	m_isResult = true;

	// 操作を止める
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(true);
	}

	if (m_timer)
	{
		m_timer->SetIsStop(true);
	}

	// 文字を表示
	ResultStr* resultStr = new ResultStr();
	resultStr->Instance(ResultStr::Type::Npc);
	resultStr->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 300.0f, 0.0f));
	SceneManager::GetInstace().GetGameObjectList().Add(resultStr);
}

/// <summary>
/// 時間切れ
/// </summary>
void GameJudge::TimeUp()
{
	if (!m_camera || !m_player || !m_enemy) return;
	m_camera->SetTarget(m_enemy);
	m_camera->SetType(PlayCamera::CAMERA_TYPE::RESULT);
	m_isResult = true;


	// 操作を止める
	if (m_playerController)
	{
		m_playerController->SetIsStop(true);
	}
	// 操作を止める
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(true);
	}

	if (m_timer)
	{
		m_timer->SetIsStop(true);
	}

	// 文字を表示
	ResultStr* resultStr = new ResultStr();
	resultStr->Instance(ResultStr::Type::Time);
	resultStr->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 300.0f, 0.0f));
	SceneManager::GetInstace().GetGameObjectList().Add(resultStr);
}

/// <summary>
/// 開始までの３秒間
/// </summary>
void GameJudge::StartThreeTime()
{
	if (!m_player || !m_enemy) return;

	// 操作を止める
	if (m_playerController)
	{
		m_playerController->SetIsStop(true);
	}
	// 操作を止める
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(true);
	}
}

/// <summary>
/// 開始
/// </summary>
void GameJudge::Start()
{
	if (!m_player || !m_enemy) return;
	m_isStart = true;
	// 操作を止める
	if (m_playerController)
	{
		m_playerController->SetIsStop(false);
	}
	// 操作を止める
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(false);
	}
}

/// <summary>
/// リザルトに移行するとき
/// </summary>
void GameJudge::ResultStart()
{
	if (m_player)
	{
		// 操作を止める
		if (m_playerController)
		{
			m_playerController->SetIsStop(true);
			m_playerHP->SetIsStop(true);
		}
	}
	if (m_enemy)
	{
		// 操作を止める
		if (m_enemyController)
		{
			m_enemyController->SetIsStop(true);
			m_enemyHP->SetIsStop(true);
		}
	}

	if (m_timer)
	{
		m_timer->SetIsStop(true);
	}
}

/// <summary>
/// プレイヤーの情報を設定する
/// </summary>
/// <param name="player"></param>
void GameJudge::SetPlayer(Player * player)
{
	if (!player)return;
	m_player = player;
	m_playerHP = m_player->GetComponent<StatusHP>();
	m_playerController = m_player->GetComponent<PlayerController>();
}

/// <summary>
/// プレイヤーの情報を初期化する
/// </summary>
void GameJudge::InitPlayerInfo()
{
	m_player = nullptr;
	m_playerHP = nullptr;
	m_playerController = nullptr;
}

/// <summary>
/// 敵の情報を設定する
/// </summary>
/// <param name="enemy"></param>
void GameJudge::SetEnemy(Enemy * enemy)
{
	if (!enemy)return;
	m_enemy = enemy;
	m_enemyHP = m_enemy->GetComponent<StatusHP>();
	m_enemyController = m_enemy->GetComponent<EnemyController>();
}

/// <summary>
/// 敵の情報を初期化する
/// </summary>
void GameJudge::InitEnemyInfo()
{
	m_enemy = nullptr;
	m_enemyHP = nullptr;
	m_enemyController = nullptr;
}

/// <summary>
/// カメラの情報を設定する
/// </summary>
/// <param name="camera"></param>
void GameJudge::SetCamera(PlayCamera * camera)
{
	m_camera = camera;
}

/// <summary>
/// タイマーの情報を設定する
/// </summary>
/// <param name="timer"></param>
void GameJudge::SetTimer(TimerCounter * timer)
{
	m_timer = timer;
}
