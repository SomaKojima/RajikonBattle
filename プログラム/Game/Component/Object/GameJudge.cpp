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
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
GameJudge::~GameJudge()
{
}

/// <summary>
/// �X�V
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
		// �v���C���[�̗̑͂��Ȃ��ꍇ
		if (m_playerHP)
		{
			if (m_playerHP->GetHP() <= 0)
			{
				m_player->Delete();
				InitPlayerInfo();
				EnemyWin();
			}
		}

		// �G�̗̑͂��Ȃ��ꍇ
		if (m_enemyHP)
		{
			if (m_enemyHP->GetHP() <= 0)
			{
				m_enemy->Delete();
				InitEnemyInfo();
				PlayerWin();
			}
		}

		// �������Ԃ𔻒�
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
/// �v���C���[���������ꍇ�̏���
/// </summary>
void GameJudge::PlayerWin()
{
	if (!m_camera || !m_player) return;
	m_camera->SetTarget(m_player);
	m_camera->SetType(PlayCamera::CAMERA_TYPE::RESULT);
	m_isResult = true;

	// ������~�߂�
	if (m_playerController)
	{
		m_playerController->SetIsStop(true);
	}

	if (m_timer)
	{
		m_timer->SetIsStop(true);
	}

	// ������\��
	ResultStr* resultStr = new ResultStr();
	resultStr->Instance(ResultStr::Type::You);
	resultStr->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 300.0f, 0.0f));
	SceneManager::GetInstace().GetGameObjectList().Add(resultStr);
}

/// <summary>
/// �G���������ꍇ�̏���
/// </summary>
void GameJudge::EnemyWin()
{
	if (!m_camera || !m_enemy) return;
	m_camera->SetTarget(m_enemy);
	m_camera->SetType(PlayCamera::CAMERA_TYPE::RESULT);
	m_isResult = true;

	// ������~�߂�
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(true);
	}

	if (m_timer)
	{
		m_timer->SetIsStop(true);
	}

	// ������\��
	ResultStr* resultStr = new ResultStr();
	resultStr->Instance(ResultStr::Type::Npc);
	resultStr->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 300.0f, 0.0f));
	SceneManager::GetInstace().GetGameObjectList().Add(resultStr);
}

/// <summary>
/// ���Ԑ؂�
/// </summary>
void GameJudge::TimeUp()
{
	if (!m_camera || !m_player || !m_enemy) return;
	m_camera->SetTarget(m_enemy);
	m_camera->SetType(PlayCamera::CAMERA_TYPE::RESULT);
	m_isResult = true;


	// ������~�߂�
	if (m_playerController)
	{
		m_playerController->SetIsStop(true);
	}
	// ������~�߂�
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(true);
	}

	if (m_timer)
	{
		m_timer->SetIsStop(true);
	}

	// ������\��
	ResultStr* resultStr = new ResultStr();
	resultStr->Instance(ResultStr::Type::Time);
	resultStr->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 300.0f, 0.0f));
	SceneManager::GetInstace().GetGameObjectList().Add(resultStr);
}

/// <summary>
/// �J�n�܂ł̂R�b��
/// </summary>
void GameJudge::StartThreeTime()
{
	if (!m_player || !m_enemy) return;

	// ������~�߂�
	if (m_playerController)
	{
		m_playerController->SetIsStop(true);
	}
	// ������~�߂�
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(true);
	}
}

/// <summary>
/// �J�n
/// </summary>
void GameJudge::Start()
{
	if (!m_player || !m_enemy) return;
	m_isStart = true;
	// ������~�߂�
	if (m_playerController)
	{
		m_playerController->SetIsStop(false);
	}
	// ������~�߂�
	if (m_enemyController)
	{
		m_enemyController->SetIsStop(false);
	}
}

/// <summary>
/// ���U���g�Ɉڍs����Ƃ�
/// </summary>
void GameJudge::ResultStart()
{
	if (m_player)
	{
		// ������~�߂�
		if (m_playerController)
		{
			m_playerController->SetIsStop(true);
			m_playerHP->SetIsStop(true);
		}
	}
	if (m_enemy)
	{
		// ������~�߂�
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
/// �v���C���[�̏���ݒ肷��
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
/// �v���C���[�̏�������������
/// </summary>
void GameJudge::InitPlayerInfo()
{
	m_player = nullptr;
	m_playerHP = nullptr;
	m_playerController = nullptr;
}

/// <summary>
/// �G�̏���ݒ肷��
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
/// �G�̏�������������
/// </summary>
void GameJudge::InitEnemyInfo()
{
	m_enemy = nullptr;
	m_enemyHP = nullptr;
	m_enemyController = nullptr;
}

/// <summary>
/// �J�����̏���ݒ肷��
/// </summary>
/// <param name="camera"></param>
void GameJudge::SetCamera(PlayCamera * camera)
{
	m_camera = camera;
}

/// <summary>
/// �^�C�}�[�̏���ݒ肷��
/// </summary>
/// <param name="timer"></param>
void GameJudge::SetTimer(TimerCounter * timer)
{
	m_timer = timer;
}
