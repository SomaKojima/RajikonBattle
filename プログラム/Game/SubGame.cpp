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
	// �Q�[���̐ݒ�
	m_game = game;

	// �����蔻��̊Ǘ��̏�����
	CollisionManager& collisionManager = CollisionManager::GetInstace();
	collisionManager.Initialize();

	// �����蔻��̋�Ԃ��쐬
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	CellRoomInfo room{ -500.0f, -500.0f, -500.0f, 500.0f, 500.0f, 500.0f };
	cLiner8TreeManager.Init(3, room);
	cLiner8TreeManager.InitCollisionMatrix();

	// �V�[���Ǘ��̏�����
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.ChangeSceneID(SceneManager::SceneID::Logo);
#ifdef _DEBUG
	sceneManager.ChangeSceneID(SceneManager::SceneID::Title);
#endif
	sceneManager.Initialize();
}

void SubGame::Update(float elapsedTime)
{
	// ���͂̍X�V
	InputManager& inputManager = InputManager::GetInstace();
	inputManager.Update(elapsedTime);
	// �}�E�X�J�[�\���̊Ǘ���������
	MouseCursorManager& mouseCursorManager = MouseCursorManager::GetInstace();

	SceneManager& sceneManager = SceneManager::GetInstace();

	// �f�o�b�O�̕������擾
	DebugString& debugString = DebugString::GetInstace();

#ifdef _DEBUG
	// �ꎞ��~����
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

	// ���Z�b�g����
	if (inputManager.GetKeyboardTracker().pressed.O)
	{
		debugString.Reset();
		sceneManager.Reset();
		mouseCursorManager.MoveCenter();
		// ��~���̏ꍇ
		if (m_isStop)
		{
			mouseCursorManager.ChangeMoveMode(m_isStop, true);
			mouseCursorManager.ChangeVisible(m_isStop, true);
		}
	}

	// �^�C�g���Ɉړ�����
	if (inputManager.GetKeyboardTracker().pressed.I)
	{
		sceneManager.ChangeSceneID(SceneManager::SceneID::Logo);
	}

#endif

	// ��~���͏������Ȃ�
	if (!m_isStop)
	{
		// �����蔻��̏���
		CollisionManager& collisionManager = CollisionManager::GetInstace();
		//collisionManager.Update(elapsedTime);

		//// �����蔻��̋�Ԃ��쐬
		CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
		cLiner8TreeManager.HitCheck();

		// �V�[���̍X�V
		sceneManager.Update(elapsedTime);
	}

	// �}�E�X�J�[�\���Ǘ����X�V
	mouseCursorManager.Update(elapsedTime);
}

void SubGame::Renderer()
{
	// �V�[���̕`��
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Render();
}

void SubGame::Finalize()
{

	// �V�[���̕`��
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.Finalize();
}
