#include "../../pch.h"
#include "PlayScene.h"
#include "../Object/GameObject.h"
#include "../Object/Car/Player.h"
#include "../Object/EnemyCar/Enemy.h"
#include "../Camera/Camera.h"
#include "../Object/Room/Room.h"
#include "../Object/SkyDome/SkyDome.h"
#include "../Object/Wall/Wall.h"
#include "../Object/GameManager/GameManager.h"
#include "../Object/LimitTimer/LimitTimer.h"
#include "../Object/Reticule/Reticule.h"
#include "../Object/HPBar/HPBar.h"
#include "../Object/ResultStr/ResultStr.h"

#include "../MouseCursor/MouseCurosrManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
}

/// <summary>
/// �����֐�
/// </summary>
void PlayScene::Instance()
{
	// �����̍쐬
	Room* room = new Room();
	room->Instance(Room::Type::Play);
	m_gameObjectList.Add(room);

	// �ǂ̍쐬
	Wall* wall = new Wall();
	wall->Instance();
	m_gameObjectList.Add(wall);

	// �X�J�C�h�[���̍쐬
	SkyDome* skydome = new SkyDome();
	skydome->Instance();
	m_gameObjectList.Add(skydome);

	// �v���C���[�̍쐬
	Player* player = new Player();
	player->Instance();
	player->GetTransform().WorldPos(Vector3(0.0f, 1.5f, 200.0f));
	m_gameObjectList.Add(player);

	// �v���C���[��HP�o�[
	HPBar* playerhpBar = new HPBar();
	playerhpBar->Instance(player, HPBar::TYPE::Player);
	playerhpBar->GetTransform().WorldPos(Vector3(540.0f, 540.0f, 0.0f));
	m_gameObjectList.Add(playerhpBar);

	// �G�̍쐬
	Enemy* enemy = new Enemy(&player->GetTransform());
	enemy->Instance();
	enemy->GetTransform().WorldDir(Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(180.0f)));
	enemy->GetTransform().WorldPos(Vector3(0, 3.0f, -100));
	m_gameObjectList.Add(enemy);

	// �G��HP�o�[
	HPBar* enemyhpBar = new HPBar();
	enemyhpBar->Instance(enemy, HPBar::TYPE::Enemy);
	enemyhpBar->GetTransform().WorldPos(Vector3(10.0f, 10.0f, 0.0f));
	m_gameObjectList.Add(enemyhpBar);

	// ���e�B�N���̍쐬
	Reticule* reticule = new Reticule(); 
	reticule->Instance();
	reticule->GetTransform().WorldPos(Vector3(400.0f, 300.0f, 0.0f));
	m_gameObjectList.Add(reticule);

	// �J�����̍쐬
	Camera* camera = new Camera();
	camera->InitializePlay(player);
	m_gameObjectList.Add(camera);
	PlayCamera* playCamera = camera->GetPlayCamera();

	// �������Ԃ̐���
	LimitTimer* limitTimer = new LimitTimer();
	limitTimer->Instance(100.0f);
	limitTimer->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 0.0f, 0.0f));
	m_gameObjectList.Add(limitTimer);
	TimerCounter* timerCounter = limitTimer->GetTimeCounter();
	
	// �Q�[���Ǘ��̍쐬
	GameManager* gameManager = new GameManager();
	gameManager->Instance(player, enemy, playCamera, timerCounter);
	m_gameObjectList.Add(gameManager);

	// �}�E�X�̔�\��
	MouseCursorManager& mouseCursorManager = MouseCursorManager::GetInstace();
	mouseCursorManager.ChangeVisible(false);
	// �}�E�X���Œ�
	mouseCursorManager.ChangeMoveMode(false);
	// �}�E�X����ʒ����Ɉړ�������
	mouseCursorManager.MoveCenter();

	m_a = MyLibrary::ADX2Le::GetInstance();
	m_a->LoadAcb(L"Play.acb", L"Play.awb");
	if (!m_a->IsPlayStateByID(m_id))
	{
		m_id = m_a->Play(0);
	}
}
