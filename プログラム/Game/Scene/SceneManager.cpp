#include "../../pch.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "LogoScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene(nullptr),
	m_currentSceneID(Title),
	m_changeSceneID(Title)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::Initialize()
{
	ChangeScene();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void SceneManager::Update(float elapsedTime)
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Update(elapsedTime);
	// �V�[���ύX���������ꍇ
	if (m_currentSceneID != m_changeSceneID)
	{
		ChangeScene();
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Render()
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Render();
}

/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
	if (!m_currentScene)return;
	m_currentScene->GetGameObjectList().Finalize();
	delete m_currentScene;
	m_currentScene = nullptr;
}

/// <summary>
/// ���݂̃V�[��������������
/// </summary>
void SceneManager::Reset()
{
	ChangeScene();
}

/// <summary>
/// �V�[����ς��鏈��
/// </summary>
void SceneManager::ChangeScene()
{
	// ���݂̃V�[���̏I������
	Finalize();

	// �V�����V�[���̍쐬
	Scene* scene = nullptr;
	switch (m_changeSceneID)
	{
	case SceneManager::Logo:
		scene = new LogoScene();
		break;
	case SceneManager::Title:
		scene = new TitleScene();
		break;
	case SceneManager::Play:
		scene = new PlayScene();
		break;
	default:
		break;
	}

	// �V�[���̍X�V
	m_currentScene = scene;
	m_currentSceneID = m_changeSceneID;

	// �V�[���̏�����
	if (!m_currentScene)return;
	m_currentScene->Instance();
	m_currentScene->GetGameObjectList().Initialize();
}
