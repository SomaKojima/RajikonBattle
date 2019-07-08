#include "../../pch.h"
#include "TitleScene.h"
#include "../Object/Room/Room.h"
#include "../Object/TitleCar/TitleCar.h"
#include "../Camera/Camera.h"
#include "../Object/TitleLogo/TitleLogo.h"
#include "../Object/StartButton/StartButton.h"
#include "../Object/ExitButton/ExitButton.h"

#include "../MouseCursor/MouseCurosrManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
}

/// <summary>
/// ����
/// </summary>
void TitleScene::Instance()
{
	// �����̍쐬
	Room* room = new Room();
	room->Instance(Room::Type::Title);
	m_gameObjectList.Add(room);

	// �Ԃ̍쐬
	GameObject* car = new TitleCar();
	car->Instance();
	car->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(7.0f, 0.0f, 0.0f));
	m_gameObjectList.Add(car);

	// �J�����̍쐬
	Camera* camera = new Camera();
	camera->InitializeTitle();
	m_gameObjectList.Add(camera);

	// �^�C�g�����S
	TitleLogo* titleLogo = new TitleLogo();
	titleLogo->Instance();
	titleLogo->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, -300.0f, 0.0f));
	m_gameObjectList.Add(titleLogo);

	// �X�^�[�g�{�^��
	StartButton* startButton = new StartButton();
	startButton->Instance();
	startButton->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 500.0f, 0.0f));
	m_gameObjectList.Add(startButton);

	// �I���{�^��
	ExitButton* exitButton = new ExitButton();
	exitButton->Instance();
	exitButton->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(55.0f, 570.0f, 0.0f));
	m_gameObjectList.Add(exitButton);


	// �}�E�X�̔�\��
	MouseCursorManager& mouseCursorManager = MouseCursorManager::GetInstace();
	mouseCursorManager.ChangeVisible(true);
	// �}�E�X���Œ�
	mouseCursorManager.ChangeMoveMode(true);

	m_a = MyLibrary::ADX2Le::GetInstance();
	m_a->LoadAcb(L"Title.acb", L"Title.awb");
	if (!m_a->IsPlayStateByID(m_id))
	{
		m_id = m_a->Play(0);
	}
}
