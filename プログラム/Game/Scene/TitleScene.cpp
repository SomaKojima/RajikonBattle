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
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
}

/// <summary>
/// 生成
/// </summary>
void TitleScene::Instance()
{
	// 部屋の作成
	Room* room = new Room();
	room->Instance(Room::Type::Title);
	m_gameObjectList.Add(room);

	// 車の作成
	GameObject* car = new TitleCar();
	car->Instance();
	car->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(7.0f, 0.0f, 0.0f));
	m_gameObjectList.Add(car);

	// カメラの作成
	Camera* camera = new Camera();
	camera->InitializeTitle();
	m_gameObjectList.Add(camera);

	// タイトルロゴ
	TitleLogo* titleLogo = new TitleLogo();
	titleLogo->Instance();
	titleLogo->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, -300.0f, 0.0f));
	m_gameObjectList.Add(titleLogo);

	// スタートボタン
	StartButton* startButton = new StartButton();
	startButton->Instance();
	startButton->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(400.0f, 500.0f, 0.0f));
	m_gameObjectList.Add(startButton);

	// 終了ボタン
	ExitButton* exitButton = new ExitButton();
	exitButton->Instance();
	exitButton->GetTransform().WorldPos(DirectX::SimpleMath::Vector3(55.0f, 570.0f, 0.0f));
	m_gameObjectList.Add(exitButton);


	// マウスの非表示
	MouseCursorManager& mouseCursorManager = MouseCursorManager::GetInstace();
	mouseCursorManager.ChangeVisible(true);
	// マウスを固定
	mouseCursorManager.ChangeMoveMode(true);

	m_a = MyLibrary::ADX2Le::GetInstance();
	m_a->LoadAcb(L"Title.acb", L"Title.awb");
	if (!m_a->IsPlayStateByID(m_id))
	{
		m_id = m_a->Play(0);
	}
}
