#pragma once

#include "../../StepTimer.h"
#include "../Utility/Singleton.h"
#include "../Object/GameObjectList.h"

/// <summary>
/// �O���錾
/// </summary>
class Game;

/// <summary>
/// �V�[���N���X
/// </summary>
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// �����֐�
	virtual void Instance() = 0;

	GameObjectList& GetGameObjectList() { return m_gameObjectList; }
protected:
	GameObjectList m_gameObjectList;
};

/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager : public Singleton<SceneManager>
{
public:
	/// <summary>
	/// �V�[������ID
	/// </summary>
	enum SceneID
	{
		Logo,
		Title,
		Play,

		Max
	};

public:
	// �R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();

	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	// ���݂̃V�[����������
	void Reset();

	// �V�[����ID��ς���
	void ChangeSceneID(SceneID sceneid) { m_changeSceneID = sceneid; }

	// �V�[����ς��鏈��
	void ChangeScene();

	// ���݂̃V�[���̃Q�[���I�u�W�F�N�g���X�g���擾
	GameObjectList& GetGameObjectList() { return m_currentScene->GetGameObjectList(); }

private:
	// ���݂̃V�[��ID
	SceneID m_currentSceneID;
	// �ς���Ƃ��Ɏg�p���鎟�̃V�[����ID
	SceneID m_changeSceneID;
	// ���݂̃V�[��
	Scene* m_currentScene;
};
